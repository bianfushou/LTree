#ifndef ASMODELSHOW_H
#define ASMODELSHOW_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QKeyEvent>

#include "model/model.h"
#include "io/iogltextlf.h"
#include "lsystem.h"

class AsmodelShow:public QOpenGLWidget
{
public:
    AsmodelShow(QWidget *parent = 0);
    ~AsmodelShow();

    void setModel(Model* model);
    void setVertpath(QString vertpath);
    void setFragpath(QString fragpath);
    static void normalizeAngle(int &angle);
    void initModel();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * event) Q_DECL_OVERRIDE;
private:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    QString vertpath;
    QString fragpath;

    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QOpenGLShaderProgram *shader;
    Model* model;
    IoGLTextlf* ioGL;
    QMatrix4x4 projM;
    QMatrix4x4 viewM;
    QMatrix4x4 worldM;
    int projId;
    int viewId;
    float scale;
};

#endif // ASMODELSHOW_H
