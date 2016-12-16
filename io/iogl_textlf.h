#ifndef IOGL_TEXTLF_H
#define IOGL_TEXTLF_H

#include <QVector3D>
#include <QOpenGLShaderProgram>
#include "lsystem.h"

class IoGL_textlf
{
public:
    IoGL_textlf();

    static QVector3D ambient;
    static QVector3D diffuse;
    static QVector3D specular;
    static QVector3D lightDir;
    static QVector3D camerPos;
    static GLfloat shininess;
    static void funGetUniform(QMap<QString,int> vio);


    static void funIoText(QOpenGLShaderProgram *const shader)
    {
        shader->setUniformValue(shader->uniformLocation("light_dir"),lightDir);
        shader->setUniformValue(shader->uniformLocation("ambient"),ambient);
        shader->setUniformValue(shader->uniformLocation("diffuse"),diffuse);
        shader->setUniformValue(shader->uniformLocation("shininess"),shininess);
        shader->setUniformValue(shader->uniformLocation("specular"),specular);
        shader->setUniformValue(shader->uniformLocation("camera_pos"),camerPos);
    }
};

#endif // IOGL_TEXTLF_H
