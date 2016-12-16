#ifndef LF2_H
#define LF2_H

#include"lf/lf.h"

class lf2:public lf
{
public:
    lf2(GLfloat nextWa,GLfloat bWa,GLfloat rightAngle,GLfloat headAngle,
        GLfloat wa,GLfloat l,LHead head,bool leaf = false,bool isBranch = false,bool init = false);
    ~lf2();

    static void lTex(GLfloat*tex ,int* in,QVector2D* tex2d,GLfloat num);
    static void bTex(GLfloat*tex ,int* in,QVector2D* tex2d,GLfloat num);
    void makeData()Q_DECL_OVERRIDE;
    void setTexId(QVector2D* texId);
    void setIn(int* in);
    void setNumTex(GLfloat numTex);
    LHead getNextHead();
    LHead getBranchHead();
    static int numTexID(GLfloat r);
    static void setHasTex(bool hasTex);
private:
    LHead branchHead;
    LHead nextHead;
    GLfloat nextWa;
    GLfloat bWa;
    GLfloat lineZ;
    GLfloat lineX;
    GLfloat rightAngle;
    GLfloat headAngle;
    GLfloat xTex;
    GLfloat numTex;
    QVector2D* texId;
    static FunTexCoord fl1;
    static FunTexCoord fl2;
    int* in;
    bool leaf;
    bool isBranch;
    static bool hasTex;
};

#endif // LF2_H
