#include <qmath.h>

#include "lf2.h"
#include "plant/tree2.h"

#define N 150

FunTexCoord lf2::fl1 = lf::fTex;
FunTexCoord lf2::fl2 = lf2::lTex;
bool lf2::hasTex = true;

lf2::lf2(GLfloat nextWa,GLfloat bWa ,GLfloat rightAngle,GLfloat headAngle, GLfloat wa,GLfloat l,LHead head,bool leaf,bool isBranch,bool init):
    nextWa(nextWa),bWa(bWa),rightAngle(rightAngle),headAngle(headAngle),leaf(leaf),isBranch(isBranch),
    lf(wa,l,head,init),in(new int[4]),numTex(0),texId(new QVector2D[4])
{
    branchHead = this->head[1];
    QMatrix4x4 result = this->head[1].getResult();
    GLfloat radians = qAbs(qDegreesToRadians(rightAngle));
    GLfloat y3 = nextWa+bWa*qCos(radians);
//    GLfloat z3 = y3*1/qTan(radians);
//    GLfloat z2 = z3 + bWa*qSin(radians);

    GLfloat z3 = bWa*qSin(radians)+2*bWa*qCos(radians);
    GLfloat z2 = z3 + bWa*qSin(radians);
    lineZ = z2;
    lineX = qSqrt(wa*wa-nextWa*nextWa);
    if(!isBranch)
    {
        branchHead.rRotate(rightAngle);
        if(rightAngle >0)
            branchHead.setPosition(result * QVector3D(0.0f,-y3,z3));
        else
            branchHead.setPosition(result * QVector3D(0.0f,y3,z3));
    }
    else
    {
        branchHead.uRotate(rightAngle);
        if(rightAngle >0)
            branchHead.setPosition(result * QVector3D(y3,0.0f,z3));
        else
            branchHead.setPosition(result * QVector3D(-y3,0.0f,z3));
    }
    nextHead = this->head[1];
    if(!isBranch)
        nextHead.hRotate(headAngle);
    nextHead.setPosition(result*QVector3D(0.0f,0.0f,z2));
}

lf2::~lf2()
{
    delete in;
    delete texId;
}

void lf2::makeData()
{
    GLfloat rs = qAcos(nextWa/wa);
    GLfloat brs = qAbs(qDegreesToRadians(rightAngle));
    int nh = (int)(nextWa*(2*M_PI - 2*rs)*N);
    int bh = (int)(bWa*2*rs*N);
    int n = (int)(nextWa*(2*M_PI)*N);
    int b = (int)(bWa*2*M_PI*N);
    int h = (int)(wa*2*M_PI*N);
    int hl = (int)(wa*(2*M_PI - 2*rs)*N);
    int nl = n - nh;
    int bl = b - bh;
    int hr = h - hl;

    QList<Vertex> bVec;
    QList<Vertex> nVec;
    QMatrix4x4 lineMat;
    QList<Vertex> h0Vec;
    QList<Vertex> h1Vec;
    if(isBranch)
    {
        bVec= getCircleVertex(b,branchHead.getResult(),rs,2*M_PI,bWa,lf::normalFun);
        nVec = getCircleVertex(n,nextHead.getResult(),-rs,
                                                 2*M_PI,nextWa,lf::normalFun);
        lineMat = head[1].getResult();
        lineMat.setColumn(3,QVector4D(0.0f,0.0f,0.0f,1.0f));
        lineMat =  QMatrix4x4(0.0f,0.0f,1.0f,0.0f,
                              1.0f,0.0f,0.0f,0.0f,
                              0.0f,1.0f,0.0f,0.0f,
                              0.0f,0.0f,0.0f,1.0f) * lineMat;
        QVector4D setlin3 = head[1].getResult()*QVector4D(nextWa,0.0f,0.0f,1.0f);
        lineMat.setColumn(3,QVector4D(setlin3.toVector3D(),1.0f));
        h0Vec = getCircleVertex(h,head[0].getResult(),rs,2*M_PI,wa,lf::normalFun);
        h1Vec = getCircleVertex(h,head[1].getResult(),rs,2*M_PI,wa,lf::normalFun);
    }
    else
    {
        bVec= getCircleVertex(b,branchHead.getResult(),-M_PI_2+rs,2*M_PI,bWa,lf::normalFun);
        nVec = getCircleVertex(n,nextHead.getResult(),-M_PI_2-rs - qDegreesToRadians(headAngle),
                                                 2*M_PI,nextWa,lf::normalFun);
        lineMat = head[1].getResult();
        lineMat.setColumn(3,QVector4D(0.0f,0.0f,0.0f,1.0f));
        lineMat =  QMatrix4x4(1.0f,0.0f,0.0f,0.0f,
                              0.0f,0.0f,-1.0f,0.0f,
                              0.0f,1.0f,0.0f,0.0f,
                              0.0f,0.0f,0.0f,1.0f) * lineMat;
        QVector4D setlin3 = head[1].getResult()*QVector4D(0.0f,-nextWa,0.0f,1.0f);
        lineMat.setColumn(3,QVector4D(setlin3.toVector3D(),1.0f));
        h0Vec = getCircleVertex(h,head[0].getResult(),-M_PI_2+rs,2*M_PI,wa,lf::normalFun);
        h1Vec = getCircleVertex(h,head[1].getResult(),-M_PI_2+rs,2*M_PI,wa,lf::normalFun);
    }


    QList<Vertex> lineNVec = getEllipseVertex((nl),lineMat,0.0f,M_PI,lineX,lineZ,lf::normal);
    QList<Vertex> lineBVec = getEllipseVertex((bl),lineMat,0.0f,M_PI,lineX,lineZ,lf::normalN);
    appendMesh(h0Vec,h1Vec,fl1,fl1,this->texId,this->in,this->numTex*l,lf::NormalVerV);

    appendMesh((h1Vec.mid(0,hl+1)),(nVec.mid(nl,nh+1)),fl1,fl1,this->texId,this->in,
               this->numTex*lineZ,lf::normalVertex);
    QList<Vertex> nfVecn = nVec.mid(0,nl+1);

    int i =0,sfv = nfVecn.size()-1;
    while(i<sfv)
    {
        Vertex tx = nfVecn[i];
        nfVecn[i] = nfVecn[sfv];
        nfVecn[sfv] = tx;
        i++;
        sfv--;
    }
    lineNVec.append(h1Vec[hl]);
    lineNVec.push_front(h1Vec[0]);
    QVector2D nVecTex[4] = {
        *(this->texId+2),*(this->texId+3),*(this->texId),*(this->texId+1)
    };
    appendMesh(nfVecn,lineNVec,fl1,fl2,nVecTex,this->in,this->numTex*lineZ,lf::normalVertex);
    lineBVec.append(h1Vec[hl]);
    lineBVec.push_front(h1Vec[h]);
    appendMesh(lineBVec,bVec.mid(0,bl+1),fl2,fl1,this->texId,this->in,
               this->numTex*lineZ/(0.7*qSin(brs)+0.5*qCos(brs)),lf::normalVertex);
    appendMesh(h1Vec.mid(hl,hr+2),bVec.mid(bl,bh+1),fl2,fl1,
               this->texId,this->in,this->numTex*lineZ/(0.7*qSin(brs)+0.5*qCos(brs)),lf::normalVertex);
}

LHead lf2::getBranchHead()
{
    return this->branchHead;
}

LHead lf2::getNextHead()
{
    return this->nextHead;
}

void lf2::lTex(GLfloat*tex ,int* in,QVector2D* tex2d,GLfloat num)
{
    if(num>0.0f)
    {
        QVector2D tex0 = *tex2d;
        QVector2D tex1 = *(tex2d+1);
        int k = *(in+1);
        int m = *in;
        int i = *(in+3);
        int n = *(in+2);
        *tex = (tex1.x() - tex0.x())/m*n*k/2 - ((tex1.x() - tex0.x())/m*n*k/2)*qCos(i*M_PI/n);
        *(tex+1) = (tex0.y() - tex1.y())*num*qSin(i*M_PI/n);
    }
}

void lf2::bTex(GLfloat *tex, int *in, QVector2D *tex2d, GLfloat num)
{

}

void lf2::setIn(int *in)
{
    *(this->in) = *in;
    *(this->in+1) = *(in+1);
}

void lf2::setTexId(QVector2D *texId)
{
    for(int i =0;i<4;i++)
        *(this->texId+i) = *(texId+i);
}

void lf2::setNumTex(GLfloat numTex)
{
    this->numTex= numTex;
}

int lf2::numTexID(GLfloat m)
{
    return (int)(m*N);
}

void lf2::setHasTex(bool has)
{
    if(has)
    {
        fl1 = lf::fTex;
        fl2 = lf2::lTex;
        hasTex = true;
    }
    else
    {
        fl1 = lf::fTexV;
        fl2 = lf2::bTex;
        hasTex = false;
    }
}
