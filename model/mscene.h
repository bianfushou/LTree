#ifndef SCENE_H
#define SCENE_H

#include<QMap>
#include <qmath.h>
#include"model/model.h"
#include "lsystem.h"
#include "vecmodel.h"
#include "mpointkey.h"
#include "io/ioshader.h"
#include "io/iogltextlf.h"

struct SKeyVal{
    MPointKey key;
    VecModel* model;
    int i;
};

class Scene
{
public:
    Scene();
    ~Scene();
    void initScene(QOpenGLFunctions_4_3_Core* f,QOpenGLShaderProgram* shader);
    void drowScene(QOpenGLFunctions_4_3_Core* f,QMatrix4x4 view,QMatrix4x4 porjM);
    void setIoTex(IoGL*);
    void makeSmodel(float x,float z,QString path,float le,float width);
    void setSmodelTex(QVector3D point,float le,float width,QString path);
    void addModel(Model* model,QVector3D vec,GLfloat scale);
    void delModel(QVector3D vec ,bool& del);

    VecModel findModel(QVector3D vec,GLfloat r,bool& find );
    VecModel getSmodel();
    SKeyVal findModel(MPointKey key,QVector3D vec,GLfloat r,GLfloat& d,bool& find );
    inline bool testBorder(QVector3D p,int & i,int &j,QVector3D & newp);

    void pastVModel(VecModel& model1,VecModel& model2);
    QMap<MPointKey,QList<VecModel*>> mapModle;
    VecModel* pVecMod;
    QVector3D border[4];
};

#endif // SCENE_H
