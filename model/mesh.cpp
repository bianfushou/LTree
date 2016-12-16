#include "mesh.h"
#include "model/model.h"

Mesh::Mesh()
{
    model.setToIdentity();
}

Mesh::Mesh(QVector<Vertex> vertices,QVector<GLuint> indices,QVector<Texture> textures):
   vertex(vertices),
   indices(indices),
   textures(textures)
{

}

Mesh::~Mesh()
{

}

void Mesh::initTex()
{
    for(int i =0;i<this->textures.size();i++)
    {
        this->textures[i].tex=0;
    }
}

void Mesh::setIndices(QVector<GLuint>& indices)
{
    this->indices = indices;
}

void Mesh::setVertex(QVector<Vertex>& vertex)
{
    this->vertex = vertex;
}

void Mesh::setTextures(const QVector<Texture>& textures)
{
    this->textures = textures;
}

void Mesh::matchTexture(QVector<Texture> text)
{
    for(int i=0;i<text.size();i++)
    {
        for(int j=0;j<this->textures.size();j++)
        {
            if(this->textures[j].path == text[i].path &&
                    this->textures[j].type == text[i].type)
            {
                this->textures[j].tex = text[i].tex;
            }
        }
    }
}

QJsonObject Mesh::toJson()
{
    QJsonObject json;
    return json;
}
 void Mesh::initializeMesh(QOpenGLFunctions_4_3_Core* f,QOpenGLShaderProgram* shader)
{
    f->glGenVertexArrays(1, &this->m_vao);
    f->glGenBuffers(1, &this->m_vbo);
    f->glGenBuffers(1, &this->m_ebo);

    f->glBindVertexArray(this->m_vao);
    f->glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, this->vertex.size() * sizeof(Vertex), this->constVertex(), GL_STATIC_DRAW);

    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->constIndices(), GL_STATIC_DRAW);


    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position[0]));

    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal[0]));

    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords[0]));
    //f->glPatchParameteri( GL_PATCH_VERTICES, 4 );
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
    this->meshModel = shader->uniformLocation("model");
}

void Mesh::printMesh(QOpenGLFunctions_4_3_Core* f,QOpenGLShaderProgram* shader,QMatrix4x4 world)
{
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for(GLuint i = 0; i < this->textures.size(); i++)
    {
        f->glActiveTexture(GL_TEXTURE0 + i);
           QString number;
           QString name = this->textures[i].type;
        if(name == "texture_diffuse")
        {
           number=(QString::number(diffuseNr));
           diffuseNr++;
        }
        else if(name == "texture_specular")
        {
            number=(QString::number(specularNr));
            specularNr++;
        }
        shader->setUniformValue(shader->uniformLocation(name+number),i);
        if(this->textures[i].tex != 0)
            this->textures[i].tex->bind();
    }
//    shader->setUniformValue(shader->uniformLocation("material.shininess"),16.0f);
    shader->setUniformValue(shader->uniformLocation("fcolor"),QVector3D(1.0f,0.0f,1.0f));
    QMatrix4x4 worldMesh = world * model;
    shader->setUniformValue(meshModel, worldMesh);
    f->glBindVertexArray(this->m_vao);
    //f->glDrawElements(GL_PATCHES, this->getIndices()->size(),GL_UNSIGNED_INT, this->constIndices() );;
//    f->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    f->glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    f->glBindVertexArray(0);
    for (GLuint i = 0; i < this->textures.size(); i++)
    {
        if(this->textures[i].tex != 0)
            this->textures[i].tex->release();
    }
}

bool Mesh::equalTexture(QVector<Texture>* t1, QVector<Texture>* t2)
{
    if(t1->size() != t2->size())
        return false;
    if(t1->size() == 0)
        return true;
    int n = t1->size();
    bool tfur[n];
    for(int k = 0;k<n;k++)
    {
        tfur[k] = true;
    }
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            if(t1->at(i).path == t2->at(j).path &&
                    t1->at(i).type == t2->at(j).type &&
                    tfur[j])
            {
                tfur[j] = false;
                break;
            }
        }
    }
    for(int f = 0;f<n;f++)
    {
        if(tfur[f])
        {
            return false;
        }
    }
    return true;
}
