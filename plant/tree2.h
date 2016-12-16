#ifndef PLANT_H
#define PLANT_H

#include <QList>

#include "plant/config.h"
#include "model/model.h"
#include "lf/lf2.h"
#include "io/ioshader.h"

struct TexTree
{
    GLfloat borderWa[2];
    int in[3][2];
    GLfloat numTex[3];
    QVector2D texId[3][4];
};

class Tree2
{
public:
    Tree2(GLfloat wa,GLfloat minWa,GLfloat l, GLfloat r1,GLfloat r2,GLfloat a0,GLfloat a2,GLfloat d,GLfloat wr1);
    Tree2(GLfloat wa,GLfloat minWa,GLfloat l,Lf2Config* lcon);

    void setTexturesLoaded(const QList<QVector<Texture>>& texture);
    void setTexTree(TexTree texTree);
    void bulidTree(bool lfTex);
    Model* bulidModel();
    ~Tree2();
    bool testTree();
protected:

    void setMeshTexture(GLfloat w,lf2* trlf);
    void buildA(GLfloat l,GLfloat w,LHead head);
    void buildB(GLfloat l,GLfloat w,LHead head);
    void buildC(GLfloat l,GLfloat w,LHead head);

protected:
    GLfloat wa;
    GLfloat minWa;
    GLfloat l;
    QList<lf*> lTf;
    Lf2Config*  lConfig;
    QList<QVector<Texture>> texturesLoaded;
    TexTree texTree;
    bool hasTex;
};

#endif // PLANT_H
