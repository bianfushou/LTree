#ifndef IOGLTEXTLF_H
#define IOGLTEXTLF_H
#include<QOpenGLShaderProgram>

#include "iogl.h"

class IoGLTextlf:public IoGL
{
public:
    IoGLTextlf();
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    QVector3D lightDir;
    QVector3D camerPos;
    GLfloat shininess;
    void makeShader(QOpenGLShaderProgram * const shader) Q_DECL_OVERRIDE;
};

#endif // IOGLTEXTLF_H
