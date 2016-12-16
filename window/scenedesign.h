#ifndef SCENEDESIGN_H
#define SCENEDESIGN_H

#include <QScrollEvent>
#include<QOpenGLWidget>
#include"model/mscene.h"
#include"Utils/camera.h"
#include"lsystem.h"
#include "io/iogltextlf.h"

struct confScene{
    GLfloat slen;
    GLfloat swid;
    QString path;
    GLfloat tlen;
    GLfloat twid;
    QVector3D ligthdir;
    GLfloat ldtr;
    bool f;
};

class SceneDesign:public QOpenGLWidget
{
    Q_OBJECT
public:
    SceneDesign(QWidget *parent = 0);
    ~SceneDesign();
    void setConf(confScene conf);
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * event) Q_DECL_OVERRIDE;
    void scrollEvent(QScrollEvent * event );

private:
    Scene* scene;
    QOpenGLShaderProgram* shader;
    IoGLTextlf* ioGL;
    Camera_Pos m_cameraPos;
    QMatrix4x4 projM;
    QMatrix4x4 viewM;
    QMatrix4x4 worldM;
    confScene conf;
    int projId;
    int viewId;
    Camera camera;
    GLfloat fov;
    Model* md;
    bool init;
    bool add;
};

#endif // SCENEDESIGN_H
