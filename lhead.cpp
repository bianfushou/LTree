#include "lhead.h"

#include <QDebug>
#include <QVector4D>

LHead::LHead(QVector3D position , QVector3D heading,QVector3D right )
{
    GLfloat z = QVector3D::dotProduct(heading,right);
    if(z <= EPSINON && z >= -EPSINON)
    {
        this->position = position;
        this->right = right.normalized();
        this->heading = heading.normalized();
        this->up = QVector3D::crossProduct(this->heading,this->right).normalized();

        this->result = QMatrix4x4(this->right.x(),this->up.x(),this->heading.x(),this->position.x(),
                      this->right.y(),this->up.y(),this->heading.y(),this->position.y(),
                      this->right.z(),this->up.z(),this->heading.z(),this->position.z(),
                      0.0f,0.0f,0.0f,1.0f);
    }else{
        qDebug()<<"前进向量和右向量不垂直";
    }
}
LHead::LHead(const LHead &head)
{
    this->position = head.position;
    this->right = head.right;
    this->up = head.up;
    this->heading = head.heading;
    this->result = QMatrix4x4(head.result);
}

LHead::~LHead()
{
}

QMatrix4x4 LHead::getResult()const
{
    return this->result;
}

QVector3D LHead::getPosition()const
{
    return this->position;
}

QVector3D LHead::getHeading()const
{
    return this->heading;
}

QVector3D LHead::getUp()const
{
    return this->up;
}

QVector3D LHead::getRight()const
{
    return this->right;
}

LHead& LHead::operator=(const LHead &head)
{
    this->position = head.getPosition();
    this->right = head.getRight();
    this->up = head.getUp();
    this->heading = head.getHeading();
    this->result = QMatrix4x4(head.getResult());

    return *this;
}

void LHead::setPosition(const QVector3D& point)
{
    this->position = point;
    this->result.setColumn(3,QVector4D(this->position,1.0f));
}

void LHead::moveHead(GLfloat f)
{
    this->position += (this->heading * f);
    this->result.setColumn(3,QVector4D(this->position,1.0f));
}

void LHead::checkRight()
{
    GLfloat s = QVector3D::dotProduct(L_Gravity,this->right);
    if(s >= EPSINON || s <= -EPSINON)
    {
        this->right = QVector3D::crossProduct(this->heading,L_Gravity).normalized();
        this->up = QVector3D::crossProduct(this->heading,this->right).normalized();
        this->result.setColumn(0,QVector4D(this->right,this->result.column(0).w()));
        this->result.setColumn(1,QVector4D(this->up,this->result.column(1).w()));
    }
}

void LHead::hRotate(GLfloat r)//以heading为轴旋转
{
    QMatrix4x4 m;
    m.rotate(r,this->heading);
    this->result = m*this->result;
    this->result.setColumn(3,QVector4D(this->position,1.0f));
    this->right = this->result.column(0).toVector3D();
    this->up = this->result.column(1).toVector3D();
    this->heading = this->result.column(2).toVector3D();
}

void LHead::rRotate(GLfloat r)//以right为轴旋转
{
    QMatrix4x4 m;
    m.rotate(r,this->right);
    this->result = m*this->result;
    this->result.setColumn(3,QVector4D(this->position,1.0f));
    this->right = this->result.column(0).toVector3D();
    this->up = this->result.column(1).toVector3D();
    this->heading = this->result.column(2).toVector3D();
}

void LHead::uRotate(GLfloat r)//以up为轴旋转
{
    QMatrix4x4 m;
    m.rotate(r,this->up);
    this->result = m*this->result;
    this->result.setColumn(3,QVector4D(this->position,1.0f));
    this->right = this->result.column(0).toVector3D();
    this->up = this->result.column(1).toVector3D();
    this->heading = this->result.column(2).toVector3D();
}
