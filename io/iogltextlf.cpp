#include "iogltextlf.h"

IoGLTextlf::IoGLTextlf():
    ambient(QVector3D(0.1,0.1,0.1)),diffuse(QVector3D(0.0,0.0,0.0)),
    specular(QVector3D(0.0,0.0,0.0)),lightDir(QVector3D(0.0,0.0,0.0)),
    camerPos(QVector3D(0.0,0.0,0.0)),shininess(0.0f)
{
}
void IoGLTextlf::makeShader(QOpenGLShaderProgram * const shader)
{
    shader->setUniformValue(shader->uniformLocation("light_dir"),lightDir);
    shader->setUniformValue(shader->uniformLocation("ambient"),ambient);
    shader->setUniformValue(shader->uniformLocation("diffuse"),diffuse);
    shader->setUniformValue(shader->uniformLocation("shininess"),shininess);
    shader->setUniformValue(shader->uniformLocation("specular"),specular);
    shader->setUniformValue(shader->uniformLocation("camera_pos"),camerPos);
}
