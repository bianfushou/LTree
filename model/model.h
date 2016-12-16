#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include "model/mesh.h"
#include <QImage>
#include <QJsonObject>
#include <QOpenGLTexture>
#include "io/ioshader.h"

#include"system/openglfunction.h"

class Model
{
public:
    Model();
    ~Model();
    virtual void addMesh(const Mesh& mesh);
    virtual void drow(QOpenGLFunctions_4_3_Core* f);
    void setTexturesLoaded(QVector<Texture> texturesLoaded);
    void setMeshList(QList<Mesh> meshList);
    QList<Mesh> getMeshList();
    QVector<Texture> getTexturesLoaded();
    void rebulidModel();
    void setMeshModel(QMatrix4x4 mModel);
    virtual void initModel(QOpenGLFunctions_4_3_Core* f,QOpenGLShaderProgram* shader);
    static QOpenGLTexture*  TextureFromFile(QString filename);
    static void TextureFromFile(Texture &texture);
    virtual QJsonObject toJson();
    void setIoShader(IoShader* ioShader);
    void makeTexture(QString path);
    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;
    QMatrix4x4 pMatrix;
    IoShader* ioShader;
    bool init;
protected:
    virtual void setShader(QOpenGLShaderProgram* shader);

    QOpenGLShaderProgram* shader;
    QList<Mesh> meshList;
    QVector<Texture> texturesLoaded;
    GLuint pId;
    GLuint vId;
};

#endif // MODEL_H
