#ifndef OPENGLFUNTION_H
#define OPENGLFUNTION_H

#include <QOpenGLContext>
#include <QMutex>

#include "lsystem.h"

class OpenGLFunction
{
public:
    static QOpenGLFunctions_4_3_Core* getOpenGLFunction();
private:
    OpenGLFunction();
    static QOpenGLFunctions_4_3_Core* f;
};

#endif // OPENGLFUNTION_H
