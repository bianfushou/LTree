#ifndef MPOINTKEY_H
#define MPOINTKEY_H
#include"model/model.h"

class MPointKey
{
public:
    MPointKey();
    MPointKey(const int x,const int z);
    friend inline bool operator<(const MPointKey &p1, const MPointKey &p2);

    static MPointKey makePoint(GLfloat x , GLfloat z);

    bool testDis(QVector3D point,GLfloat r);

    int  getx()const;
    int  getz()const;
    int x();
    int z();

private:
    int lx;
    int lz;
};
inline bool operator<(const MPointKey &p1, const MPointKey &p2)
{
    if(p1.getx()<p2.getx())
    {
        return true;
    }
    else if(p1.getx()>p2.getx())
    {
        return false;
    }
    else if(p1.getz()<p2.getz())
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif // MPOINTKEY_H
