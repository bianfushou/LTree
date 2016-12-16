#ifndef IOGL_H
#define IOGL_H

#include<QOpenGLShaderProgram>

class IoGL
{
public:
    IoGL();
    virtual void makeShader(QOpenGLShaderProgram * const shader)=0;
};

#endif // IOGL_H
