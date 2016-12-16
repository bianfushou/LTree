#ifndef TREECONTROL_H
#define TREECONTROL_H

#include <QJsonObject>

#include "plant/tree2.h"
#include "model/model.h"
class treeControl
{
public:
    treeControl();
    Model* tree2Model(QJsonObject configJson);
    Model* tree2TexModel(QJsonObject configJson);
private:
    bool treeJson(GLfloat& r1,GLfloat& r2,GLfloat& a0,GLfloat& a2,GLfloat& d,GLfloat& wr,
                  GLfloat& wa,GLfloat& minWa,GLfloat& l,QJsonObject& configJson);
    bool treeTexJson(QString& path,GLfloat& wa,GLfloat& h,int &shininess,GLfloat& minw,QString f,QJsonObject& configJson);
};

#endif // TREECONTROL_H
