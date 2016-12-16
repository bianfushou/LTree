#ifndef MARK_H
#define MARK_H

#include"model/mesh.h"
#include<QOpenGLShaderProgram>

class Mark
{
public:
    Mark();
    enum ACTION{
        LOOK,
        FIND,
        ADD,
        ALTER
    };

    void makePoint();
    void setPoint(QVector3D position,QVector3D front,QVector3D up,QVector3D right);
    void toinit(QOpenGLFunctions_4_3_Core* f);
    Mesh pointMark;
    float scale;
    QOpenGLShaderProgram *program;
    bool init;
};

#endif // MARK_H
