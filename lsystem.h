#ifndef LSYSTEM
#define LSYSTEM

#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLContext>

const float EPSINON = 0.000001f;
const QString rootPath("D:/Qt/Ltree/");
inline bool equalZero(float x){
    if(x<EPSINON && x> -EPSINON)
        return true;
    return false;
}

#endif // LSYSTEM

