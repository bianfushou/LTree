#include "mpointkey.h"

MPointKey::MPointKey()
{

}

MPointKey::MPointKey(const int x,const int z):
    lx(x),lz(z) {}
MPointKey MPointKey::makePoint(GLfloat x , GLfloat z)
{
    int px = (int)(x/2);
    int pz = (int)(z/2);
    if(px<0)
    {
        px --;
    }
    else if(px == 0 && x<0)
    {
        px --;
    }
    if(pz>0)
    {
        pz++;
    } else if(pz ==0 && z>0)
    {
        pz++;
    }
    return MPointKey(px,pz);
}
bool MPointKey::testDis(QVector3D point,GLfloat r)
{
    if(point.distanceToLine(QVector3D(lx*2.0f,point.y(),lz*2.0f),QVector3D((lx+1)*2.0f,point.y(),lz*2.0f))<r)
    {
        return true;
    }
    if(point.distanceToLine(QVector3D((lx+1)*2.0f,point.y(),(lz-1)*2.0f),QVector3D((lx+1)*2.0f,point.y(),lz*2.0f))<r)
    {
        return true;
    }
    if(point.distanceToLine(QVector3D((lx+1)*2.0f,point.y(),(lz-1)*2.0f),QVector3D((lx)*2.0f,point.y(),(lz-1)*2.0f))<r)
    {
        return true;
    }
    if(point.distanceToLine(QVector3D((lx)*2.0f,point.y(),(lz)*2.0f),QVector3D((lx)*2.0f,point.y(),(lz-1)*2.0f))<r)
    {
        return true;
    }
    return false;
}

 int MPointKey::getx()const
{
    return lx;
}
int MPointKey::getz()const
{
    return lz;
}

int MPointKey::x()
{
   return lx;
}
int MPointKey::z()
{
   return lz;
}
