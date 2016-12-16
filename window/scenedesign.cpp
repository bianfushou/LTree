#include "scenedesign.h"
#include "io/iomodel.h"

SceneDesign::SceneDesign(QWidget *parent):
    QOpenGLWidget(parent),
    shader(0),
    ioGL(new IoGLTextlf),
    camera(QVector3D(0.0f, -0.35f, 1.0f)),
    scene(new Scene),
    init(false),
    add(false)
{
    m_cameraPos.firstPos = true;
    m_cameraPos.deltaTime = 0.01f;
    m_cameraPos.lastFrame = 0.0f;
    fov = 45.0f;
}

SceneDesign::~SceneDesign()
{

}

void SceneDesign::setConf(confScene conf)
{
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
    this->conf = conf;
    scene->makeSmodel(this->conf.slen,this->conf.swid,
                      this->conf.path,this->conf.tlen,this->conf.twid);
    scene->setIoTex(ioGL);
    scene->initScene(f,shader);
    init = true;
}

void SceneDesign::initializeGL()
{
    worldM.setToIdentity();
    viewM.setToIdentity();
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
    f->initializeOpenGLFunctions();
    f->glClearColor(0.3f,0.3f,0.3f,1.0f);
    shader = new QOpenGLShaderProgram;
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,rootPath
                                    +QString("shaderCode/textlf.vert"));
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,rootPath
                                    +QString("shaderCode/textlf.frag"));
    shader->link();
    ioGL->ambient =QVector3D(0.1f,0.1f,0.1f);
    ioGL->camerPos = -(viewM.column(3).toVector3D());
    ioGL->diffuse = QVector3D(1.0f,1.0f,1.0f);
    ioGL->specular = QVector3D(1.0f,1.0f,1.0f);
    ioGL->shininess = 16.0f;
    ioGL->lightDir = QVector3D(0.0f,-0.5f,-0.5f);
    if(init)
    {
        scene->initScene(f,shader);
    }
    projM.perspective(fov, this->width() / this->height(), 0.01f, 100.0f);

}

void SceneDesign::paintGL()
{
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);
    if(init)
    {

        viewM = camera.GetViewMatrix();
        ioGL->camerPos = -(viewM.column(3).toVector3D());
        scene->drowScene(f,viewM,projM);
        if(add)
        {
//            md->mMatrix = worldM;
            md->vMatrix = viewM;
            md->pMatrix = projM;
//            md->drow(f);
            scene->initScene(f,shader);
            add = false;
        }
    }
}

void SceneDesign::resizeGL(int width, int height)
{
    projM.setToIdentity();
    projM.perspective(fov, width / height, 0.01f, 100.0f);
}

void SceneDesign::mouseMoveEvent(QMouseEvent *event)
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

void SceneDesign::mousePressEvent(QMouseEvent *event)
{
    this->m_cameraPos.lastPos = event->pos();
    this->update();
}

void SceneDesign::keyPressEvent(QKeyEvent * event)
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
    if(event->key() == Qt::Key_K)
    {
        if (fov >= 1.0f && fov <= 45.0f)
            fov = fov-1.0f;
        if(fov<1.0f)
            fov = 1.1f;
        projM.setToIdentity();
        projM.perspective(fov, this->width() / this->height(), 0.01f, 100.0f);
    }
    if(event->key() == Qt::Key_L)
    {
        if (fov >= 1.0f && fov <= 60.0f)
            fov ++;
        if(fov>60.0f)
            fov = 59.5f;
        projM.setToIdentity();
        projM.perspective(fov, this->width() / this->height(), 0.01f, 100.0f);
    }
    if(event->key() == Qt::Key_N)
    {
        IoModel* m = IoModel::getIo();
        md = m->pasteModel();
        if(md!= 0)
        {
            md->ioShader->setfGL(ioGL);
            QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
//            md->initModel(f,shader);
            scene->addModel(md,
                        QVector3D(camera.Position.x()+camera.Front.x(),-0.5f,camera.Position.z()+camera.Front.z())
                        ,m->scale);
            add=true;
        }
    }
    if(event->key() == Qt::Key_P)
    {
        bool t;
        scene->delModel(QVector3D(camera.Position.x()+camera.Front.x(),-0.5f,camera.Position.z()+camera.Front.z())
                        ,t);
    }
    this->update();
}

void SceneDesign::scrollEvent(QScrollEvent *event)
{

}
