#include "ioshader.h"

IoShader::IoShader():fGL(0)
{
    this->fShader = funIoSh;
}


void IoShader::setValueShader(QOpenGLShaderProgram *const shader)
{
    if(fGL == 0)
        fShader(shader);
    else
        fGL->makeShader(shader);
}

void IoShader::setfShader(FunShader fS)
{
    this->fShader = fS;
}

void IoShader::setfGL(IoGL* fgl)
{
    this->fGL =fgl;
}
