#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLShaderProgram>
#include <QScrollEvent>

#include"model/model.h"
#include"model/mesh.h"
#include"lf/lf.h"
#include"Utils/camera.h"
#include"lsystem.h"
#include "io/iogltextlf.h"

class treeWidget :public QOpenGLWidget
{
    Q_OBJECT
public:
    treeWidget(QWidget *parent = 0);
    ~treeWidget();
    void cleanup();
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * event) Q_DECL_OVERRIDE;
    void scrollEvent(QScrollEvent * event );

    bool eventFilter(QObject *, QEvent *)Q_DECL_OVERRIDE;
private:
    QOpenGLShaderProgram *m_program;
    int m_proj;
    int m_view;
    IoGLTextlf* ioGL;
    Camera_Pos m_cameraPos;
    QMatrix4x4 m_projM;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    Mesh m_mesh;
    Camera camera;
    float fov;
    QList<Model*> listModel;
};

#endif // TREEWIDGET_H
