#include "asmodelshow.h"
#include "io/iomodel.h"

AsmodelShow::AsmodelShow(QWidget* parent):
    QOpenGLWidget(parent),
    shader(0),
    model(new Model),
    ioGL(new IoGLTextlf),
    xRot(0),
    yRot(0),
    zRot(0)
{
    ioGL->ambient =QVector3D(0.1f,0.1f,0.1f);
    ioGL->camerPos = -(viewM.column(3).toVector3D());
    ioGL->diffuse = QVector3D(1.0f,1.0f,1.0f);
    ioGL->specular = QVector3D(1.0f,1.0f,1.0f);
    ioGL->shininess = 16.0f;
    ioGL->lightDir = QVector3D(0.0f,-0.5f,-0.5f);
    scale = 1.0;
}

AsmodelShow::~AsmodelShow()
{
    if(ioGL != 0)
    {
        delete this->ioGL;
        this->ioGL = 0;
    }
    delete model;
}

void AsmodelShow::setModel(Model *asmodel)
{
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
    if(asmodel != 0)
    {
        model->setMeshList(asmodel->getMeshList());
        model->setTexturesLoaded(asmodel->getTexturesLoaded());
        model->ioShader->setfGL(ioGL);
        model->initModel(f,shader);
        update();
    }
}

void AsmodelShow::setVertpath(QString vertpath)
{
    this->vertpath = vertpath;
}
void AsmodelShow::setFragpath(QString fragpath)
{
    this->fragpath = fragpath;
}

void AsmodelShow::normalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void AsmodelShow::initModel()
{
    this->model = 0;
    update();
}

void AsmodelShow::initializeGL()
{
    worldM.setToIdentity();
    viewM.setToIdentity();
    viewM.translate(0.0f,0.0f,-7.0f);
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
    f->initializeOpenGLFunctions();
    f->glClearColor(0.0f,1.0f,1.0f,1.0f);
    shader = new QOpenGLShaderProgram;
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex,rootPath +vertpath);
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment,rootPath+fragpath);
    if(model != 0)
    {
        model->ioShader->setfGL(ioGL);
        model->initModel(f,shader);
    }
    projM.perspective(45.0f, this->width() / this->height(), 0.01f, 100.0f);

}

void AsmodelShow::paintGL()
{
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);
    if(model!=0)
    {
        worldM.setToIdentity();
        worldM.rotate((xRot / 16.0f), 1, 0, 0);
        worldM.rotate(yRot / 16.0f, 0, 1, 0);
        worldM.rotate(zRot / 16.0f, 0, 0, 1);
        worldM.scale(scale);

        model->mMatrix = worldM;
        model->vMatrix = viewM;
        model->pMatrix = projM;
        model->drow(f);
    }
}

void AsmodelShow::resizeGL(int width, int height)
{
    projM.setToIdentity();
    projM.perspective(45.0f, width / height, 0.01f, 100.0f);
}

void AsmodelShow::setXRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        update();
    }
}

void AsmodelShow::setYRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void AsmodelShow::setZRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        update();
    }
}

void AsmodelShow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

void AsmodelShow::mousePressEvent(QMouseEvent *event)
{
    this->lastPos = event->pos();
}

void AsmodelShow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_K)
    {
        scale *=0.9;
        update();
    }
    if(event->key() == Qt::Key_L)
    {
        scale /=0.9;
        update();
    }
    if(event->key() == Qt::Key_Y)
    {
        IoModel* m = IoModel::getIo();
        m->setCopyModel(model);
        m->scale = scale;
    }
    if(event->key() == Qt::Key_B)
    {
        IoModel* m = IoModel::getIo();
        m->setCopyModel(model,worldM);
        m->scale = scale;
    }
}
