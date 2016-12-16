#ifndef VECMODEL_H
#define VECMODEL_H

#include<QOpenGLShaderProgram>
#include"model.h"

class Path{
public:
    bool addpath(QOpenGLShader::ShaderTypeBit ftype,QString fpath)
    {
        switch(ftype)
        {
        case QOpenGLShader::Vertex:
            path[0] = fpath;
            break;
        case QOpenGLShader::Fragment:
            path[1] = fpath;
            break;
        case QOpenGLShader::Geometry:
            path[2] = fpath;
            break;
        case QOpenGLShader::TessellationControl:
            path[3] = fpath;
            break;
        case QOpenGLShader::TessellationEvaluation:
            path[4] = fpath;
            break;
        case QOpenGLShader::Compute:
            path[5] = fpath;
            break;
        default:
            return false;
        }
        return true;
    }
    QString path[6];
};

class VecModel{
public:
    VecModel(){}
    VecModel(QVector3D f,Model* model,GLfloat scale):f(f),model(0),scale(scale)
    {
        if(model != 0)
        {
            this->model = new Model();
            this->model->setMeshList(model->getMeshList());
            this->model->setTexturesLoaded(model->getTexturesLoaded());
            world();
        }
    }
    ~VecModel()
    {
        if(model != 0)
            delete model;
    }

    inline void world()
    {
        this->model->mMatrix.setToIdentity();
        this->model->mMatrix.scale(scale);
        f.setY(f.y()-0.005);
        this->model->mMatrix.setColumn(3,QVector4D(f,1.0f));
    }
    QVector3D f;
    GLfloat scale;
    Model* model;
    QList<Path> path;
};

#endif // VECMODEL_H
