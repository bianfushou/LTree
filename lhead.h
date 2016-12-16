#ifndef LHEAD_H
#define LHEAD_H

#include <qopengl.h>
#include <QMatrix4x4>
#include <QVector3D>

#include "lsystem.h"

const QVector3D L_Gravity = QVector3D(0.0f,-1.0f,0.0f);//指向地心
const QVector3D L_Compass = QVector3D(0.0f,0.0f,1.0f);//指向南方

class LHead
{
public:
    LHead(QVector3D position = QVector3D(0.0f,0.0f,0.0f), QVector3D heading= QVector3D(0.0f,0.0f,1.0f),QVector3D right = QVector3D(1.0f,0.0f,0.0f));
    LHead(const LHead &head);
    ~LHead();

    QMatrix4x4 getResult()const;
    QVector3D getPosition()const;
    QVector3D getHeading()const;
    QVector3D getUp()const;
    QVector3D getRight()const;

    LHead& operator=(const LHead& head);
    void setPosition(const QVector3D& point);

    void moveHead(GLfloat f);
    void checkRight();
    void hRotate(GLfloat r);//以heading为轴旋转
    void rRotate(GLfloat r);//以right为轴旋转
    void uRotate(GLfloat r);//以up为轴旋转

private:
    QVector3D position;
    QVector3D heading;
    QVector3D right;
    QVector3D up;
    QMatrix4x4 result;
};

#endif // LHEAD_H
