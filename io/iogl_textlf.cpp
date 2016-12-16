#include "iogl_textlf.h"

IoGL_textlf::IoGL_textlf()
{

}

QVector3D IoGL_textlf::ambient = QVector3D(0.1,0.1,0.1);
QVector3D IoGL_textlf::diffuse = QVector3D(0.0,0.0,0.0);
QVector3D IoGL_textlf::specular = QVector3D(0.0,0.0,0.0);
QVector3D IoGL_textlf::lightDir = QVector3D(0.0,0.0,0.0);
QVector3D IoGL_textlf::camerPos = QVector3D(0.0,0.0,0.0);
GLfloat IoGL_textlf::shininess = 0.0f;

void IoGL_textlf::funGetUniform(QMap<QString,int> vio)
{
   if(!vio.contains("light_dir"))
       vio.insert("light_dir",0);
   if(!vio.contains("ambient"))
       vio.insert("ambient",0);
   if(!vio.contains("diffuse"))
       vio.insert("diffuse",0);
   if(!vio.contains("specular"))
       vio.insert("specular",0);
   if(!vio.contains("shininess"))
       vio.insert("shininess",0);
   if(!vio.contains("camera_pos"))
       vio.insert("camera_pos",0);

}
