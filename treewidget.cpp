#include "treewidget.h"
#include "shaderCode/shadercode.h"
#include<QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QOpenGLContext>
#include "lf/lf2.h"
#include "model/model.h"
#include "system/openglfunction.h"
#include "io/iogltextlf.h"
#include "io/ioshader.h"
#include"io/iomodel.h"

IoShader *ios=0;

treeWidget::treeWidget(QWidget *parent):
    QOpenGLWidget(parent),
    m_program(0),
    camera(QVector3D(0.0f, 0.0f, 1.0f))
{
    m_cameraPos.firstPos = true;
    m_cameraPos.deltaTime = 0.01f;
    m_cameraPos.lastFrame = 0.0f;
    fov = 45.0f;
}

treeWidget::~treeWidget()
{
    cleanup();
}

void treeWidget::cleanup()
{
    makeCurrent();

    delete m_program;
    m_program = 0;
    doneCurrent();
}

void setTextures( lf2* fl)
{
    Texture tex1,tex2;
    tex1.type = "texture_diffuse";
    tex2.type = "texture_specular";
    tex1.tex=Model::TextureFromFile("D:/Qt/Ltree/image/t4.jpg");
    tex2.tex = Model::TextureFromFile("D:/Qt/Ltree/image/t4.jpg");
    tex1.path = "D:/Qt/Ltree/image/t4.jpg";
    tex2.path = "D:/Qt/Ltree/image/t4.jpg";
    QVector<Texture> textu ={
        tex1,tex2
    };
    int m = lf2::numTexID(40.0f/400);
    int in[2] = {
        m,1
    };
    QVector2D vec[4]={
        QVector2D(0.0f,0.0f),QVector2D(1.0f,0.0f),QVector2D(0.0f,1.0f),QVector2D(1.0f,1.0f)
    };
    fl->setIn(in);
    fl->setTexId(vec);
    fl->setNumTex(1.0f/40.0f*400);
    fl->setTextures(textu);
}

void treeWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &treeWidget::cleanup);
    LHead head(QVector3D(0.0f,-0.2f,-0.0f),QVector3D(0.0f,1.0f,0.0f),QVector3D(1.0f,0.0f,0.0f));
    lf2 *fi =new lf2(0.04f,0.03f,30.0f,137.5f,0.05f,0.3f,head,false,false,false);
    setTextures( fi);
    lf2::setHasTex(true);
    fi->makeData();
    this->m_mesh = fi->getMesh();
    delete fi;
     m_world.setToIdentity();
     //m_world.scale(0.5f);
     m_camera.setToIdentity();
    m_camera.translate(0.0f,0.0f,-0.5f);
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
     f->initializeOpenGLFunctions();
     f->glClearColor(0.0f,1.0f,1.0f,1.0f);

     m_program = new QOpenGLShaderProgram;
     QString path("D:/Qt/Ltree/");
    //QString date = path;
     m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,path
                                        +QString("shaderCode/textlf.vert"));
     m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,path
                                        +QString("shaderCode/textlf.frag"));
     m_program->link();
     m_program->bind();
     m_proj = m_program->uniformLocation("projection");
     m_view = m_program->uniformLocation("view");

     m_mesh.initializeMesh(f,m_program);
     m_program->release();
     ioGL->ambient =QVector3D(0.1f,0.1f,0.1f);
     ioGL->camerPos = -(viewM.column(3).toVector3D());
     ioGL->diffuse = QVector3D(1.0f,1.0f,1.0f);
     ioGL->specular = QVector3D(1.0f,1.0f,1.0f);
     ioGL->shininess = 16.0f;
     ioGL->lightDir = QVector3D(0.0f,-0.5f,-0.5f);
     m_projM.perspective(fov, this->width() / this->height(), 0.01f, 100.0f);

}

void treeWidget::paintGL()
{
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();

    //time_t currentFrame = time(nullptr);
    //m_cameraPos.deltaTime = (GLfloat) difftime(currentFrame,m_cameraPos.lastFrame);
    //m_cameraPos.lastFrame = currentFrame;
    f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);
    //m_world.setToIdentity();
    //m_world.rotate(10.0f,0.0f,1.0f,0.0f);
    m_camera = camera.GetViewMatrix();
    m_program->bind();
    m_program->setUniformValue(m_proj, m_projM);
    m_program->setUniformValue(m_view,m_camera);
    QMatrix4x4 ss;
    ss.setToIdentity();
    m_mesh.printMesh(f,m_program,m_world);
    m_program->release();

}

void treeWidget::resizeGL(int width, int height)
{
    m_projM.setToIdentity();
    m_projM.perspective(fov, width / height, 0.01f, 100.0f);
}

void treeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_cameraPos.firstPos)
    {
        this->m_cameraPos.lastPos = event->pos();
    }
    m_cameraPos.firstPos = false;
    int dx = event->x() - this->m_cameraPos.lastPos.x();
    int dy = this->m_cameraPos.lastPos.y() - event->y();
    this->m_cameraPos.lastPos = event->pos();
    camera.ProcessMouseMovement(dx,dy);
    this->update();
}

void treeWidget::mousePressEvent(QMouseEvent *event)
{
    this->m_cameraPos.lastPos = event->pos();
    this->update();
}

void treeWidget::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_W)
    {
        camera.ProcessKeyboard(Camera::FORWARD, m_cameraPos.deltaTime);
    }
    if(event->key() == Qt::Key_S)
    {
        camera.ProcessKeyboard(Camera::BACKWARD, m_cameraPos.deltaTime);
    }
    if(event->key() == Qt::Key_A)
    {
        camera.ProcessKeyboard(Camera::LEFT, m_cameraPos.deltaTime);
    }
    if(event->key() == Qt::Key_D)
    {
        camera.ProcessKeyboard(Camera::RIGHT, m_cameraPos.deltaTime);
    }
    if(event->key() == Qt::Key_R)
    {
        if (fov >= 1.0f && fov <= 45.0f)
            fov --;
        if(fov<1.0f)
            fov = 1.0f;
    }
    if(event->key() == Qt::Key_L)
    {
        if (fov >= 1.0f && fov <= 45.0f)
            fov ++;
        if(fov>45.0f)
            fov = 45.0f;
    }
    if(event->key() == Qt::Key_N)
    {
        IoModel* m = IoModel::getIo();
        Model* model = new Model();
        model->setMeshList(m->pasteModel()->getMeshList());
        model->setTexturesLoaded(m->pasteModel()->getTexturesLoaded());
        QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
        model->initModel(f,m_program);
        listModel.append(model);
    }
    if(event->key() == Qt::Key_P)
    {

    }
    this->update();
}

void treeWidget::scrollEvent(QScrollEvent *event)
{

}

bool treeWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this) {
        if (event->type() == QEvent::KeyPress) {
            keyPressEvent(static_cast<QKeyEvent *>(event));
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            mousePressEvent(static_cast<QMouseEvent *>(event));
            return true;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        return QOpenGLWidget::eventFilter(watched,event);
    }else
    {
        return QOpenGLWidget::eventFilter(watched,event);
    }
}

