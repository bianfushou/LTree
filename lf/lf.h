#ifndef LF_H
#define LF_H
#include "lhead.h"
#include <QVector>
#include <qmath.h>
#include "model/mesh.h"

typedef void (*FunType)(GLfloat* ,int );
typedef QVector3D (*Nor)(const QVector3D& voc,const QVector3D& up,QVector3D befVoc);
typedef void (*NorVertex)(Vertex* ver1,Vertex* ver2,const Vertex* ver3);
typedef void (*FunTexCoord)(GLfloat* ,int*,QVector2D*,GLfloat );
class lf
{
public:
    explicit lf(GLfloat wa,GLfloat l,LHead head, bool init);
    lf(const lf &lf);
    ~lf();

    virtual const Mesh& getMesh() final { return f_mesh; }
    virtual void initLf() ;

    void setTextures(const QVector<Texture>& textures);
    virtual  QVector<QVector3D> getVector(int n);
    virtual  QList<QVector3D> getOrderVector(int n,QMatrix4x4 trans);
    QList<QVector3D> getCircleVector(int n, QMatrix4x4 trans,GLfloat beginRadian,GLfloat radians,GLfloat r);
    QList<QVector3D> getEllipseVector(int n, QMatrix4x4 trans,GLfloat beginRadian, GLfloat radians,GLfloat rX, GLfloat rY);
    QList<Vertex> getCircleVertex(int n, QMatrix4x4 trans, GLfloat beginRadian, GLfloat radians, GLfloat r,Nor);
    QList<Vertex> getEllipseVertex(int n, QMatrix4x4 trans, GLfloat beginRadian, GLfloat radians, GLfloat rX, GLfloat rY,Nor);

    virtual QList<Vertex> getVertexs(const QList<QVector3D>& vertex,const LHead &lh,Nor normalFun);
    virtual void appendMeshVertex(const QList<QVector3D>& vertex,QList<GLuint> &indices,const LHead &lh,FunTexCoord f1,Nor normalFun
                                  ,                         QVector2D ver1T0,QVector2D ver1T1,GLfloat numTex);
    void appendMeshVertexs(const QList<Vertex> &ver,QList<GLuint> &indices,FunTexCoord f1,QVector2D ver1T0,QVector2D ver1T1,
                                                GLfloat numTex);
    virtual void appendMesh(QList<Vertex> ver1,QList<Vertex> ver2,FunTexCoord f1,FunTexCoord f2,
                            QVector2D* ver1T,int* in, GLfloat numTex,NorVertex nor);

    void setIndices(const QList<GLuint>& indice1,const QList<GLuint>& indice2);
    static QVector3D normalFun(const QVector3D &voc,const QVector3D& up, QVector3D pos);
    static QVector3D normalF(const QVector3D& voc,const QVector3D& up,QVector3D befVoc);
    static QVector3D normal(const QVector3D& voc,const QVector3D& up,QVector3D befVoc);
    static QVector3D normalN(const QVector3D& voc,const QVector3D& up,QVector3D befVoc);
    static QVector3D normalV(const QVector3D& voc,const QVector3D& up,QVector3D befVoc);

    static void normalVertex(Vertex *nor1,Vertex *nor2, const Vertex *nor3);
    static void NormalVerV(Vertex *nor1,Vertex *nor2, const Vertex *nor3);

    static void fTex(GLfloat* tex,int* in,QVector2D* tex2d,GLfloat num);
    static void fTexV(GLfloat* tex,int* in,QVector2D* tex2d,GLfloat num);
    virtual void makeData();
    void removeVertexList(QList<Vertex> &list, int e);
protected:
    //virtual void makeTextures(QVector<Texture> textures);
    LHead head[2];
    Mesh f_mesh;
    GLfloat wa;
    GLfloat l;
private:
    void appendFirMesh(QList<Vertex> ver1,QList<Vertex> ver2,FunTexCoord f1,FunTexCoord f2,
                       QVector2D* ver1T,int* in, GLfloat numTex,NorVertex nor);
    void appendSecMesh(QList<Vertex> ver1,QList<Vertex> ver2,FunTexCoord f1,FunTexCoord f2,
                       QVector2D* ver1T,int* in, GLfloat numTex,NorVertex nor);
    void appendEqualNumMesh(QList<Vertex> ver1,QList<Vertex> ver2,FunTexCoord f1,FunTexCoord f2,
                            QVector2D* ver1T,int* in, GLfloat numTex,NorVertex nor);
};

#endif // LF_H
