#include "mark.h"
#include "lsystem.h"

Mark::Mark():scale(1.0)
{
    makePoint();
//    this->program = new QOpenGLShaderProgram;
//    this->program->addShaderFromSourceFile(QOpenGLShader::Vertex,rootPath +"shaderCode/textlf.vert");
//    this->program->addShaderFromSourceFile(QOpenGLShader::Fragment,rootPath+"shaderCode/textlf.frag");
//    this->program->link();
    init = false;
}

void Mark::makePoint()
{
    QVector<Vertex> vert = {
        {{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f}},
        {{-0.01f,0.0f,0.015f},{0.0f,1.0f,0.0f},{0.0f,0.0f}},
        {{0.01f,0.0f,0.015f},{0.0f,1.0f,0.0f},{0.0f,0.0f}}
    };
    QVector<GLuint> buf = {
        0,1,2
    };
    this->pointMark.setVertex(vert);
    this->pointMark.setIndices(buf);
}

void Mark::setPoint(QVector3D position, QVector3D front,QVector3D up, QVector3D right)
{
    this->pointMark.model.setColumn(0,QVector4D(right,0.0f));
    this->pointMark.model.setColumn(1,QVector4D(up,0.0f));
    this->pointMark.model.setColumn(2,QVector4D(front,0.0f));
    this->pointMark.model.setColumn(3,QVector4D(position+front,1.0f));
}

void Mark::toinit(QOpenGLFunctions_4_3_Core *f)
{
    this->program = new QOpenGLShaderProgram;
    this->program->addShaderFromSourceFile(QOpenGLShader::Vertex,rootPath +"shaderCode/textlf.vert");
    this->program->addShaderFromSourceFile(QOpenGLShader::Fragment,rootPath+"shaderCode/textlf.frag");
    this->program->link();
    this->pointMark.initializeMesh(f,this->program);
}
