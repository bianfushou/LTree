#include "lf/lf.h"

lf::lf(GLfloat wa,GLfloat l,LHead head,bool init):
    wa(wa),l(l)
{
    this->head[0] = head;
    this->head[1] = head;
    this->head[1].moveHead(l);
    if(init)
    {
        makeData();
    }
}

lf::lf(const lf &lf)
{
    this->head[0] = lf.head[0];
    this->head[1] = lf.head[1];
    this->f_mesh = lf.f_mesh;
    this->l = lf.l;
    this->wa =lf.wa;
}

lf::~lf()
{

}

void lf::makeData()
{
    QVector<Vertex>* vertex = this->f_mesh.getVertex();
    QVector<GLuint>* indices = this->f_mesh.getIndices();

    int s = (int)(wa*2*M_PI*500);
    QVector<QVector3D> vec = getVector(s);

    int size = vec.size();
    QMatrix4x4 result0 = head[0].getResult();
    QMatrix4x4 result1 = head[1].getResult();

    for(int i=0;i<size;i++) {
        const QVector3D vi = vec[i];
        QVector3D position0 = result0 * vi;
        QVector3D position1 = result1 * vi;
        QVector3D nor = (position0 - head[0].getPosition()).normalized();
        Vertex vert[2]={
            {
               {position0.x(), position0.y(),position0.z()},
               {nor.x(), nor.y(), nor.z()},
               {i*2.0f/size, 3.0f }
            },
            {
                {position1.x(), position1.y(),position1.z()},
                {nor.x(), nor.y(), nor.z()},
                {i*2.0f/size, 0.0f }
            }
        };
        vertex->push_back(vert[0]);
        vertex->push_back(vert[1]);
        if(i>0)
        {
            QVector<GLuint> ind = {(unsigned)2*i,(unsigned)2*i+1,(unsigned)2*i-1,(unsigned)2*i,(unsigned)2*i-1,(unsigned)2*i-2};
            (*indices) += ind;
        }
    }
}

 QVector<QVector3D> lf::getVector(int n)
{
    QVector<QVector3D> ver;
    if(n%2 != 0 && n>4)
        n++;
    else if(n<4)
        n=4;
    GLfloat angle = (2 * M_PI) / n;
    QVector3D prev = wa*QVector3D(1.0f,0.0f,0.0f);
    GLfloat s = qSin(angle);
    GLfloat c = qCos(angle);
    for(int i=0;i<=n;i++)
    {
        QVector3D v;
        if(i == 0)
        {
            v = prev;
        }
        else
        {
            v.setX(prev.x()*c - prev.y()*s);
            v.setY(prev.y()*c + prev.x()*s);
            v.setZ(0.0f);
            prev = v;
        }
        ver.push_back(v);
    }
    return ver;
}

 QList<QVector3D> lf::getCircleVector(int n, QMatrix4x4 trans,GLfloat beginRadian,GLfloat radians , GLfloat r)
 {
     QList<QVector3D> ver;
     if(n<4)
         n=4;
     GLfloat angle = radians / n;
     GLfloat rad = beginRadian;
     for(int i = 0; i <= n ;i ++)
     {
         QVector3D v;
         v.setX(r*qCos(rad));
         v.setY(r*qSin(rad));
         v.setZ(0.0f);
         v = trans * v;
         ver.append(v);
         rad += angle;
     }
     return ver;
 }

 QList<Vertex> lf::getCircleVertex(int n, QMatrix4x4 trans, GLfloat beginRadian, GLfloat radians, GLfloat r,Nor fn)
 {
     QList<Vertex> ver;
     if(n<4)
         n=4;
     GLfloat angle = radians / n;
     GLfloat rad = beginRadian;
     for(int i = 0; i < n ;i ++)
     {
         QVector3D v;

         v.setX(r*qCos(rad));
         v.setY(r*qSin(rad));
         v.setZ(0.0f);
         v = trans * v;
         QVector3D nor = fn(v,trans.column(2).toVector3D(),trans.column(3).toVector3D());
         Vertex vert = {
             {v.x(),v.y(),v.z()},
             {nor.x(),nor.y(),nor.z()},
             {0.0f,0.0f}
         };
         ver.append(vert);
         rad += angle;
     }
     if(ver.size() == n)
     {
         ver.append(ver.first());
     }
     return ver;
 }

  QList<QVector3D> lf::getEllipseVector(int n, QMatrix4x4 trans,GLfloat beginRadian, GLfloat radians,GLfloat rX, GLfloat rY)
  {
      QList<QVector3D> ver;
      if(n<4)
          n=4;
      GLfloat angle = radians / n;
      GLfloat rad = beginRadian;
      for(int s = 0; s <= n; s++)
      {
          QVector3D v;
          v.setX(rX*qCos(rad));
          v.setY(rY*qSin(rad));
          v.setZ(0.0f);
          v = trans*v;
          ver.append(v);
          rad += angle;
      }
      return ver;
  }

  QList<Vertex> lf::getEllipseVertex(int n, QMatrix4x4 trans, GLfloat beginRadian, GLfloat radians,
                                     GLfloat rX, GLfloat rY,Nor fn)
  {
      QList<Vertex> ver;
      if(n<4)
          n=4;
      GLfloat angle = radians / n;
      GLfloat rad = beginRadian;
      QVector3D befv;
      for(int s = 0; s <= n; s++)
      {
          QVector3D v;
          v.setX(rX*qCos(rad));
          v.setY(rY*qSin(rad));
          v.setZ(0.0f);
          v = trans*v;
          if(s == 0)
          {
             befv.setX(rX*qCos(rad-angle));
             befv.setY(rY*qSin(rad-angle));
             befv.setZ(0.0f);
          }
          QVector3D nor=fn(v,trans.column(2).toVector3D(),befv);
          Vertex vert =
          {
              {v.x(),v.y(),v.z()},
              {nor.x(),nor.y(),nor.z()},
              {0.0f,0.0f}
          };
          befv = v;
          ver.append(vert);
          rad += angle;
      }
      return ver;
  }

 void lf::setIndices(const QList<GLuint>& indice1, const QList<GLuint>& indice2)
 {
     int n = indice1.size();
     int b = indice2.size();
     int e = 0,d = 0;
     int sum=0;

     if(n>b)
     {
        e = n - b;
        d = b/e;
        sum = n;
     }
     else if(b!=n)
     {
         e = b - n;
         d = n/e;
         sum = b;
     }
     else
     {
         sum = n;
     }
     QVector<GLuint>* indices = this->f_mesh.getIndices();
    int i=0,j=0;
    while(i<sum)
    {
        for(int k = 0;k<=d && e>0;k++)
        {
            if(k == d)
            {
                i++;
                e--;
            }
            else if(i!=0)
            {
                if(n>b)
                {
                    QVector<GLuint> buf = {indice1[i],indice2[j],indice2[j-1],indice1[i],indice2[j-1],indice1[i-1]};
                    (*indices) += buf;
                }
                else
                {
                    QVector<GLuint> buf = {indice1[j],indice2[i],indice2[i-1],indice1[j],indice2[i-1],indice1[j-1]};
                    (*indices) += buf;
                }
            }
            i++;
            j++;
        }
        if(e == 0)
        {
            if(n>b)
            {
                QVector<GLuint> buf = {indice1[i],indice2[j],indice2[j-1],indice1[i],indice2[j-1],indice1[i-1]};
                (*indices) += buf;
            }
            else
            {
                QVector<GLuint> buf = {indice1[j],indice2[i],indice2[i-1],indice1[j],indice2[i-1],indice1[j-1]};
                (*indices) += buf;
            }
            i++;
            j++;
        }
    }
 }
 
 QList<QVector3D> lf::getOrderVector(int n,QMatrix4x4 trans)
 {
    return getCircleVector(n,trans,0.0f,M_PI * 2,wa);
 }

 QList<Vertex> lf::getVertexs(const QList<QVector3D> &vertex, const LHead &lh,Nor normalFun)
 {
    QList<Vertex> meshVertex;
    for(int i = 0;i<vertex.size();i++)
    {
        QVector3D normal = normalFun(vertex[i] , lh.getHeading() ,vertex[i-1]);
        Vertex ver = {
            {vertex[i].x(),vertex[i].y(),vertex[i].z()},
            {normal.x(),normal.y(),normal.z()},
            {0.0f,0.0f}
        };
        meshVertex.append(ver);
    }
    return meshVertex;
 }

void lf::appendMeshVertexs(const QList<Vertex> &ver,QList<GLuint> &indices,FunTexCoord f1,
                           QVector2D ver1T0,QVector2D ver1T1,GLfloat numTex)
 {
     QVector<Vertex>* meshVertex = this->f_mesh.getVertex();
     int len = meshVertex->size();
     for(int i = 0;i<ver.size();i++)
     {        
         Vertex vert = ver[i];
//         f1((vert.TexCoords),i,ver.size(),ver1T0,ver1T1,numTex);
         meshVertex->push_back(vert);
         indices.append(i+len);
     }
 }

void lf::appendMeshVertex(const QList<QVector3D> &vertex, QList<GLuint> &indices, const LHead &lh,FunTexCoord f1,Nor normalFun,
                          QVector2D ver1T0,QVector2D ver1T1,GLfloat numTex)
{
    QVector<Vertex>* meshVertex = this->f_mesh.getVertex();
    int ind = meshVertex->size();
    for(int i = 0;i<vertex.size();i++)
    {
        QVector3D normal;
        normal = normalFun(vertex[i] , lh.getHeading() ,lh.getPosition());
        Vertex ver = {
            {vertex[i].x(),vertex[i].y(),vertex[i].z()},
            {normal.x(),normal.y(),normal.z()},
            {0.0f,0.0f}
        };
//        f1((ver.TexCoords),i,vertex.size(),ver1T0,ver1T1,numTex);
        indices.append(ind+i);
        meshVertex->push_back(ver);
    }
}

QVector3D lf::normalFun(const QVector3D &voc,const QVector3D& up, QVector3D pos)
{
    return voc - pos;
}

 QVector3D lf::normalF(const QVector3D &voc,const QVector3D& up, QVector3D befVoc)
{
    return QVector3D::crossProduct( voc-befVoc ,up);
}
 QVector3D lf::normal(const QVector3D &voc, const QVector3D &up, QVector3D befVoc)
 {
     return up;
 }
 QVector3D lf::normalN(const QVector3D &voc, const QVector3D &up, QVector3D befVoc)
 {
     return QVector3D(0.0f,0.0f,0.0f) - up;
 }
 QVector3D lf::normalV(const QVector3D &voc, const QVector3D &up, QVector3D befVoc)
 {

 }

void lf::normalVertex(Vertex *nor1, Vertex *nor2, const Vertex *nor3)
{
    QVector3D vec1(nor1->Position[0],nor1->Position[1],nor1->Position[2]);
    QVector3D vec2(nor2->Position[0],nor2->Position[1],nor2->Position[2]);
    QVector3D vec3(nor3->Position[0],nor3->Position[1],nor3->Position[2]);
    QVector3D vec4 = QVector3D::crossProduct(vec1-vec3,vec2-vec1);
    nor1->Normal[0] = vec4.x();
    nor1->Normal[1] = vec4.y();
    nor1->Normal[2] = vec4.z();
    nor2->Normal[0] = vec4.x();
    nor2->Normal[1] = vec4.y();
    nor2->Normal[2] = vec4.z();
}

void lf::NormalVerV(Vertex *nor1, Vertex *nor2, const Vertex *nor3)
{
}

 void lf::fTex(GLfloat* tex,int* in,QVector2D* tex2d,GLfloat num)
{
    if(num>0.0f)
    {
        int k = *(in+1);
        int m = *(in);
        int i = *(in+3);
        int n = *(in+2);
        *tex = i * ( (*(tex2d+1)).x() - (*tex2d).x() )* k / m;
        *(tex+1) = num*(*tex2d).y();
    }
}

 void lf::fTexV(GLfloat* tex,int* in,QVector2D* tex2d,GLfloat num)
 {

 }

void lf::setTextures(const QVector<Texture> &textures)
{
    this->f_mesh.setTextures(textures);
}

void lf::appendMesh(QList<Vertex> ver1,QList<Vertex> ver2,FunTexCoord f1,FunTexCoord f2,
                    QVector2D* ver1T,int* in, GLfloat numTex,NorVertex nor)
{
    int n = ver1.size();
    int b = ver2.size();
    int e = 0;

    if(n>b)
    {
       e = n - b;
       if(e>b)
       {
           removeVertexList(ver1,b+b-1);
       }
       appendFirMesh(ver1, ver2, f1,f2,ver1T,in,numTex,nor);
    }
    else if(b!=n)
    {
        e = b - n;
        if(e>n)
        {
            removeVertexList(ver2,n+n-1);
        }
        appendSecMesh(ver1, ver2, f1,f2,ver1T,in,numTex,nor);
    }
    else
    {
        appendEqualNumMesh(ver1, ver2, f1,f2,ver1T,in,numTex,nor);
    }
}

void lf::initLf()
{
    makeData();
}

void lf::removeVertexList(QList<Vertex> &list, int e)
{
    int size = list.size();
    if(size>e)
    {
        int n = size - e;
        int d = size /n;
        int f = d/2;
        int i = 0;
        while(i<list.size())
        {
            list.removeAt(f+i);
            i=i+d-1;
        }
    }
}

void lf::appendFirMesh(QList<Vertex> ver1,QList<Vertex> ver2,FunTexCoord f1,FunTexCoord f2,
                       QVector2D* ver1T,int* in, GLfloat numTex,NorVertex nor)
{
    QVector<Vertex>* meshVertex = this->f_mesh.getVertex();
    QVector<GLuint>* indices = this->f_mesh.getIndices();

    int sum = ver1.size();
    int b = ver2.size();
    int m = meshVertex->size();
    int e = sum - b;
    int d = b/e;
    int i=0,j=0;
    bool end = false;
    while(i<sum)
    {
        for(int k = 0;k<=d && e>0;k++)
        {
            if(k == d)
            {
                *(in+2) = sum-1;
                *(in+3) = i;
                f1((ver1[i].TexCoords),in,ver1T,numTex);
                meshVertex->push_back(ver1[i]);
                i++;
                e--;
                if(e == 0)
                {
                    end = true;
                    if(i == sum)
                    {
                        QVector<GLuint> buf = {m+i+j-1,m+i+j-2,m+i+j-3};
                         (*indices) += buf;
                        nor(&((*meshVertex)[m+i+j-1]),&((*meshVertex)[m+i+j-2]),&((*meshVertex)[m+i+j-3]));
                    }
                }
                continue;
            }
            else
            {
                *(in+2) = sum-1;
                *(in+3) = i;
                f1((ver1[i].TexCoords),in,ver1T,numTex);
                meshVertex->push_back(ver1[i]);
                *(in+2) = b-1;
                *(in+3) = j;
                f2((ver2[j].TexCoords),in,ver1T+2,numTex);
                meshVertex->push_back(ver2[j]);
                if(i>0)
                {
                    if(k!=0){
                        QVector<GLuint> buf = {m+i+j,m+j+i+1,m+j+i-1,m+i+j,m+i+j-1,m+i+j-2};
                         (*indices) += buf;
                    }
                    else{
                        QVector<GLuint> buf = {m+i+j,m+j+i+1,m+j+i-1,m+i+j+1,m+i+j-2,m+i+j-1,m+i+j-1,m+i+j-2,m+i+j-3};
                         (*indices) += buf;
                    }
                    nor(&((*meshVertex)[m+i+j]),&((*meshVertex)[m+i+j+1]),&((*meshVertex)[m+i+j-1]));
                }
            }
            i++;
            j++;
        }
        if(e == 0 && i< sum )
        {
            *(in+2) = sum-1;
            *(in+3) = i;
            f1((ver1[i].TexCoords),in,ver1T,numTex);
            meshVertex->push_back(ver1[i]);
            *(in+2) = b-1;
            *(in+3) = j;
            f2((ver2[j].TexCoords),in,ver1T+2,numTex);
            meshVertex->push_back(ver2[j]);
            if(end)
            {
                QVector<GLuint> buf = {m+i+j,m+j+i+1,m+j+i-1,m+i+j+1,m+i+j-2,m+i+j-1,m+i+j-1,m+i+j-2,m+i+j-3};
                 (*indices) += buf;
                end = false;
            }else
            {
                QVector<GLuint> buf = {m+i+j,m+j+i+1,m+j+i-1,m+i+j,m+i+j-1,m+i+j-2};
                (*indices) += buf;
            }
            nor(&((*meshVertex)[m+i+j]),&((*meshVertex)[m+i+j+1]),&((*meshVertex)[m+i+j-1]));
            i++;
            j++;
        }
    }
}

void lf::appendSecMesh(QList<Vertex> ver1,QList<Vertex> ver2,FunTexCoord f1,FunTexCoord f2,
                       QVector2D* ver1T,int* in, GLfloat numTex,NorVertex nor)
{
    QVector<Vertex>* meshVertex = this->f_mesh.getVertex();
    QVector<GLuint>* indices = this->f_mesh.getIndices();

    int sum = ver2.size();
    int n = ver1.size();
    int e = sum - n;
    int m = meshVertex->size();
    int d = n/e;
    int i=0,j=0;
    bool end = false;
    while(i<sum)
    {
        for(int k = 0;k<=d && e>0;k++)
        {
            if(k == d)
            {
                *(in+2) = sum-1;
                *(in+3) = i;
                f2((ver2[i].TexCoords),in,ver1T+2,numTex);
                meshVertex->push_back(ver2[i]);
                i++;
                e--;
                if(e == 0)
                {
                    end = true;
                    if(i == sum)
                    {
                        QVector<GLuint> buf = {m+i+j-1,m+i+j-2,m+i+j-3};
                         (*indices) += buf;
                        nor(&((*meshVertex)[m+i+j-1]),&((*meshVertex)[m+i+j-2]),&((*meshVertex)[m+i+j-3]));
                    }
                }
                continue;
            }
            else
            {
                *(in+2) = n-1;
                *(in+3) = j;
                f1((ver1[j].TexCoords),in,ver1T,numTex);
                meshVertex->push_back(ver1[j]);
                *(in+2) = sum-1;
                *(in+3) = i;
                f2((ver2[i].TexCoords),in,ver1T+2,numTex);
                meshVertex->push_back(ver2[i]);
                if(i>0)
                {
                    if(k!=0){
                        QVector<GLuint> buf = {m+i+j,m+j+i+1,m+j+i-1,m+i+j,m+i+j-1,m+i+j-2};
                         (*indices) += buf;
                    }
                    else{
                        QVector<GLuint> buf = {m+i+j,m+j+i+1,m+j+i-1,m+i+j-1,m+i+j-3,m+i+j,m+i+j-3,m+i+j-1,m+i+j-2};
                         (*indices) += buf;
                    }
                    nor(&((*meshVertex)[m+i+j]),&((*meshVertex)[m+i+j+1]),&((*meshVertex)[m+i+j-1]));
                }
            }
            i++;
            j++;
        }
        if(e == 0 && i< sum )
        {
            *(in+2) = n-1;
            *(in+3) = j;
            f1((ver1[j].TexCoords),in,ver1T,numTex);
            meshVertex->push_back(ver1[j]);
            *(in+2) = sum-1;
            *(in+3) = i;
            f2((ver2[i].TexCoords),in,ver1T+2,numTex);
            meshVertex->push_back(ver2[i]);
            if(end)
            {
                QVector<GLuint> buf = {m+i+j,m+j+i+1,m+j+i-1,m+i+j-1,m+i+j-3,m+i+j,m+i+j-3,m+i+j-1,m+i+j-2};
                 (*indices) += buf;
                end = false;
            }
            else
            {
                QVector<GLuint> buf = {m+i+j,m+j+i+1,m+j+i-1,m+i+j,m+i+j-1,m+i+j-2};
                (*indices) += buf;
            }
            nor(&((*meshVertex)[m+i+j]),&((*meshVertex)[m+i+j+1]),&((*meshVertex)[m+i+j-1]));
            i++;
            j++;
        }
    }
}

void lf::appendEqualNumMesh(QList<Vertex> ver1,QList<Vertex> ver2,FunTexCoord f1,FunTexCoord f2,
                            QVector2D* ver1T,int* in, GLfloat numTex,NorVertex nor)
{
    QVector<Vertex>* meshVertex = this->f_mesh.getVertex();
    QVector<GLuint>* indices = this->f_mesh.getIndices();

    int sum = ver1.size();
    int i =0;
    int m = meshVertex->size();
    while( i<sum )
    {
        *(in+2) = sum-1;
        *(in+3) = i;
        f1((ver1[i].TexCoords),in,ver1T,numTex);
        meshVertex->push_back(ver1[i]);
        *(in+2) = sum-1;
        *(in+3) = i;
        f2((ver2[i].TexCoords),in,ver1T+2,numTex);
        meshVertex->push_back(ver2[i]);
        if(i>0)
        {
            QVector<GLuint> buf = {m+i+i,m+i+i+1,m+i+i-1,m+i+i,m+i+i-1,m+i+i-2};
            (*indices) += buf;
            nor(&((*meshVertex)[m+i+i]),&((*meshVertex)[m+i+i+1]),&((*meshVertex)[m+i+i-1]));
        }
        i++;
    }
}
