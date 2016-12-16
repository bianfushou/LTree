#ifndef IOSHADER_H
#define IOSHADER_H

#include<QOpenGLShaderProgram>

#include "iogl.h"

typedef void (*FunShader)( QOpenGLShaderProgram *const shader);
static void funIoSh(QOpenGLShaderProgram *const shader)
{
}

class IoShader
{
public:
    IoShader();
    void makeShader( QOpenGLShaderProgram * const shader);
    void setValueShader( QOpenGLShaderProgram * const shader);
    void setfShader(FunShader fS);
    void setfGL(IoGL* fgl);
private:
    FunShader fShader;
    IoGL* fGL;
};

#endif // IOSHADER_H
