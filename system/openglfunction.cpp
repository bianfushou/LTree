#include "openglfunction.h"

OpenGLFunction::OpenGLFunction()
{
}

QOpenGLFunctions_4_3_Core* OpenGLFunction::getOpenGLFunction()
{
    if (f == nullptr)
    {
        QMutex mutex;
        mutex.lock();
        if (f == nullptr)
        {
            f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
        }
        mutex.unlock();
    }

    return f;
}
