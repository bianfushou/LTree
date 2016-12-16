#include "model.h"

Model::Model():
    pId(0),vId(0),shader(0),ioShader(new IoShader),init(false)
{
    mMatrix.setToIdentity();
    vMatrix.setToIdentity();
    pMatrix.setToIdentity();
}

Model::~Model()
{
    if(this->ioShader != 0)
    {
        delete this->ioShader;
    }
    if(init)
    {
        for(int i=0;i<this->texturesLoaded.size();i++)
        {
            if(this->texturesLoaded[i].tex != 0)
                delete this->texturesLoaded[i].tex;
        }
    }
}

QJsonObject Model::toJson()
{

}

void Model::addMesh(const Mesh& mesh )
{
    meshList.append(mesh);
}

void Model::setShader(QOpenGLShaderProgram *shader)
{
    this->shader = shader;
}

void Model::setIoShader(IoShader* ioShader)
{
    this->ioShader = ioShader;
}

void Model::setTexturesLoaded(QVector<Texture> texturesLoaded)
{
    if(!this->texturesLoaded.empty())
    {
        if(init)
        {
            for(int i=0;i<this->texturesLoaded.size();i++)
            {
                if(this->texturesLoaded[i].tex != 0 && init)
                    delete this->texturesLoaded[i].tex;
            }
        }
    }
    init = false;
    this->texturesLoaded = texturesLoaded;
    for(int i=0;i<this->texturesLoaded.size();i++)
    {
        this->texturesLoaded[i].tex = 0;
    }
}
void Model::setMeshList(QList<Mesh> meshList)
{
    this->meshList = meshList;
    this->mMatrix.setToIdentity();
    this->pMatrix.setToIdentity();
    this->vMatrix.setToIdentity();
}

QList<Mesh> Model::getMeshList()
{
    return this->meshList;
}

QVector<Texture> Model::getTexturesLoaded()
{
    return this->texturesLoaded;
}

void Model::rebulidModel()
{
    if(init)
    {
        for(int p=0;p<this->texturesLoaded.size();p++)
        {
            if(this->texturesLoaded[p].tex != 0)
            {
                delete this->texturesLoaded[p].tex;
                this->texturesLoaded[p].tex = 0;
            }
        }
        init = false;
    }
    QList<Mesh> buferMesh;
    int i = 0;
    while(i<this->meshList.size())
    {
        int j = 0;
        while(j<buferMesh.size())
        {
            if(Mesh::equalTexture(meshList[i].getTexture(),buferMesh[j].getTexture())
                    && buferMesh[j].getIndices()->size()<6000)
            {
                QVector<GLuint>*bin = buferMesh[j].getIndices();
                QVector<GLuint>*min = meshList[i].getIndices();
                QVector<Vertex>* bver = buferMesh[j].getVertex();
                QVector<Vertex>* mver = meshList[i].getVertex();
                QVector<GLuint> mbin = *min;
                int sk = bver->size();
                *bver += (*mver);
                for(int km = 0;km<mbin.size();km++)
                {
                    mbin[km] += sk;
                }
                *bin += mbin;
                break;
            }
            j++;
        }
        if(j == buferMesh.size())
        {
            buferMesh.push_back(meshList[i]);
        }
        i++;
    }
    if(meshList.size() > buferMesh.size())
    {
        meshList = buferMesh;
    }
}

void Model::setMeshModel(QMatrix4x4 mModel)
{
    int i = 0;
    while(i<this->meshList.size())
    {
        meshList[i].model = mModel;
        i++;
    }
}

void Model::drow(QOpenGLFunctions_4_3_Core* f)
{
    if(init)
    {
        int len = meshList.size(), i = 0;
        shader->bind();
        shader->setUniformValue(pId, pMatrix);
        shader->setUniformValue(vId, vMatrix);
        ioShader->setValueShader(shader);
        while(i<len)
        {
            meshList[i].printMesh(f,shader,mMatrix);
            i++;
        }
        shader->release();
    }
}
void Model::makeTexture(QString path)
{
    Texture vtex1,vtex2;
    vtex1.type = "texture_diffuse";
    vtex2.type = "texture_specular";
    vtex1.path = path;
    vtex2.path = path;
    QVector<Texture> vtextu ={
        vtex1,vtex2
    };
    this->texturesLoaded = vtextu;
    for(int i = 0;i<this->meshList.size();i++)
    {
        meshList[i].setTextures(vtextu);
    }
}
void Model::initModel( QOpenGLFunctions_4_3_Core *f,QOpenGLShaderProgram* shader)
{
    init = true;
    setShader(shader);
    int len = meshList.size(), i = 0;
    this->shader->bind();
    pId = this->shader->uniformLocation("projection");
    vId = this->shader->uniformLocation("view");
    for(int j=0;j<this->texturesLoaded.size();j++)
    {
        this->texturesLoaded[j].tex = TextureFromFile(this->texturesLoaded[j].path);
    }
    while(i<len)
    {
        meshList[i].initializeMesh(f,shader);
        meshList[i].matchTexture(this->texturesLoaded);
        i++;
    }
    this->shader->release();
}

QOpenGLTexture* Model::TextureFromFile(QString filename)
{
    QOpenGLTexture* textureID;
    QImage image;

    if ( image.load(filename) )
    {
        textureID = new QOpenGLTexture(image.mirrored());
        textureID->setWrapMode(QOpenGLTexture::Repeat);
        textureID->setMagnificationFilter(QOpenGLTexture::Linear);
        textureID->setMinificationFilter(QOpenGLTexture::Nearest);
        return textureID;
    }
    return 0;
}

void Model::TextureFromFile(Texture &texture)
{
    texture.tex=TextureFromFile(texture.path);
}
