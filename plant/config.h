#ifndef CONFIG
#define CONFIG
#include <qopengl.h>
#include<QtMath>
#include "lsystem.h"

class Lf2Config{
public:
    static Lf2Config*  getConfig(GLfloat r1,GLfloat r2,GLfloat a0,GLfloat a2,GLfloat d,GLfloat wr1)
    {
        GLfloat wr2 =qSqrt(1-wr1*wr1);
        return  new Lf2Config( r1, r2, a0,  a2,  d,  wr1,  wr2);
    }

    GLfloat r1;
    GLfloat r2;
    GLfloat a0;
    GLfloat a2;
    GLfloat d;
    GLfloat wr1;
    GLfloat wr2;
private:
    Lf2Config(GLfloat r1,GLfloat r2,GLfloat a0,GLfloat a2,GLfloat d,GLfloat wr1,GLfloat wr2):
        r1(r1),r2(r2),a0(a0),a2(a2),d(d),wr1(wr1),wr2(wr2)
    {
    }
};
#endif // CONFIG

