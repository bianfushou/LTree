#include "tree2.h"
#include "lsystem.h"
Tree2::Tree2(GLfloat wa,GLfloat minWa,GLfloat l, GLfloat r1,GLfloat r2,GLfloat a0,GLfloat a2,GLfloat d,GLfloat wr1):
    wa(wa),minWa(minWa),l(l)
{
    lConfig=Lf2Config::getConfig( r1,r2,a0,a2, d, wr1);
}

Tree2::Tree2(GLfloat wa,GLfloat minWa, GLfloat l,Lf2Config* lcon):
    wa(wa),minWa(minWa),l(l),lConfig(lcon)
{
}

bool Tree2::testTree()
{
    if(equalZero(wa)||equalZero(wa-minWa)||equalZero(minWa)||wa<minWa)
        return false;
    else if(equalZero(lConfig->r1)||lConfig->r1>0.999f)
        return false;
    else if(equalZero(lConfig->r2)||lConfig->r2>0.999f)
        return false;
    else if(equalZero(l))
        return false;
    else if(equalZero(lConfig->a0) || equalZero(lConfig->a2))
        return false;
    else if(equalZero(lConfig->wr1))
        return false;
    else
        return true;
}

Tree2::~Tree2()
{
    if(lConfig != nullptr)
    {
        delete lConfig;
    }
    QList<lf*>::iterator lfIter = lTf.begin();
    while(lfIter != lTf.end())
    {
        if((*lfIter) != nullptr)
        {
            delete (*lfIter);
            *lfIter = nullptr;
        }
        lfIter++;
    }
}

Model* Tree2::bulidModel()
{
    Model* model = new Model();
    QList<lf*>::const_iterator lfIter = lTf.constBegin();
    while(lfIter != lTf.constEnd())
    {
       model->addMesh((*lfIter)->getMesh());
        lfIter++;
    }
    if(this->texturesLoaded.size() == 3)
    {
        QVector<Texture> text = this->texturesLoaded[0]+this->texturesLoaded[1]+
            this->texturesLoaded[2];
        model->setTexturesLoaded(text);
    }
    return model;
}

void Tree2::setTexturesLoaded(const QList<QVector<Texture>> &texture)
{
    this->texturesLoaded = texture;
}

void Tree2::setMeshTexture(GLfloat w, lf2 *trlf)
{
    if(w>this->texTree.borderWa[0])
    {
        trlf->setTextures(this->texturesLoaded[0]);
        trlf->setIn(this->texTree.in[0]);
        trlf->setTexId(this->texTree.texId[0]);
        trlf->setNumTex(this->texTree.numTex[0]);
    }
    else if(w>this->texTree.borderWa[1])
    {
        trlf->setTextures(this->texturesLoaded[1]);
        trlf->setIn(this->texTree.in[1]);
        trlf->setTexId(this->texTree.texId[1]);
        trlf->setNumTex(this->texTree.numTex[1]);
    }
    else
    {
        trlf->setTextures(this->texturesLoaded[2]);
        trlf->setIn(this->texTree.in[2]);
        trlf->setTexId(this->texTree.texId[2]);
        trlf->setNumTex(this->texTree.numTex[2]);
    }
}

void Tree2::setTexTree(TexTree texTree)
{
    this->texTree = texTree;
}


void Tree2::bulidTree(bool lfTex)
{
    LHead head(QVector3D(0.0f,0.0f,0.0f),QVector3D(0.0f,1.0f,0.0f),QVector3D(1.0f,0.0f,0.0f));
    this->hasTex = lfTex;
    lf2::setHasTex(lfTex);
    buildA(this->l,this->wa,head);
}

void Tree2::buildA(GLfloat l, GLfloat w,LHead head)
{
    if(w>minWa)
    {
            lf2 *fi =new lf2(w*this->lConfig->wr1,w*this->lConfig->wr2,this->lConfig->a0,this->lConfig->d,
                             w,l,head,false,false,false);
            if(hasTex)
            {
                setMeshTexture(w, fi);
            }
            fi->makeData();
            this->lTf.append(fi);
            buildA(l*this->lConfig->r1,w*this->lConfig->wr1,fi->getNextHead());
            LHead bHead=fi->getBranchHead();
            bHead.checkRight();
            buildB(l*this->lConfig->r2,w*this->lConfig->wr2,bHead);
    }
}

void Tree2::buildB(GLfloat l, GLfloat w, LHead head)
{
    if(w>minWa)
    {
        lf2 *fi =new lf2(w*this->lConfig->wr1,w*this->lConfig->wr2,-this->lConfig->a2,
                         0.0f,w,l,head,false,true,false);
        if(hasTex)
            setMeshTexture(w, fi);
        fi->makeData();
        this->lTf.append(fi);
        LHead bHead=fi->getBranchHead();
        bHead.checkRight();
        LHead nHead=fi->getNextHead();
        nHead.checkRight();
        buildC(l*this->lConfig->r1,w*this->lConfig->wr1,nHead);
        buildC(l*this->lConfig->r2,w*this->lConfig->wr2,bHead);
    }
}

void Tree2::buildC(GLfloat l, GLfloat w, LHead head)
{
    if(w>minWa)
    {
        lf2 *fi =new lf2(w*this->lConfig->wr1,w*this->lConfig->wr2,this->lConfig->a2,
                         0.0f,w,l,head,false,true,false);
        if(hasTex)
            setMeshTexture(w, fi);
        fi->makeData();
        this->lTf.append(fi);
        LHead bHead=fi->getBranchHead();
        bHead.checkRight();
        LHead nHead=fi->getNextHead();
        nHead.checkRight();
        buildB(l*this->lConfig->r1,w*this->lConfig->wr1,nHead);
        buildB(l*this->lConfig->r2,w*this->lConfig->wr2,bHead);
    }
}
