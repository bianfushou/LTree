#ifndef MESH_H
#define MESH_H

#include <QtGui/QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QJsonObject>
#include <QOpenGLTexture>

#include "lsystem.h"

struct Vertex {
    // Position
    GLfloat Position[3];
    // Normal
    GLfloat Normal[3];
    // TexCoords
    GLfloat TexCoords[2];
};

struct Texture {
    QOpenGLTexture* tex;
    QString type;
    QString path;
};

class Mesh
{
public:
    Mesh();
    Mesh(QVector<Vertex>,QVector<GLuint>,QVector<Texture>);
    ~Mesh();

    virtual const Vertex* constVertex()const final { return vertex.constData(); }
    virtual const GLuint* constIndices()const final { return indices.constData(); }

    virtual  QVector<Vertex>* getVertex() final { return &vertex; }
    virtual  QVector<GLuint>* getIndices() final { return &indices; }
    virtual  QVector<GLuint>* getPatchesIndices() final { return &patchesIndices; }
    virtual  QVector<Texture>* getTexture() final {return &textures;}

    void initTex();
    void initializeMesh(QOpenGLFunctions_4_3_Core* f,QOpenGLShaderProgram* shader);
    void printMesh(QOpenGLFunctions_4_3_Core* f,QOpenGLShaderProgram* shader, QMatrix4x4 world);
    void matchTexture(QVector<Texture>);
    void setVertex(QVector<Vertex>& vertex);
    void setIndices(QVector<GLuint>& indices);
    void setTextures(const QVector<Texture>& textures);
    virtual QJsonObject toJson();
    static bool equalTexture(QVector<Texture>* t1, QVector<Texture>* t2);
    QMatrix4x4 model;
private:
    QVector<Vertex> vertex;
    QVector<GLuint> indices;
    QVector<GLuint> patchesIndices;
    QVector<Texture> textures;

    int meshModel;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};

#endif // MESH_H
