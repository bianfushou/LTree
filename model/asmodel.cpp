#include "asmodel.h"

AsModel::AsModel()
{
}

void AsModel::loadModel(QString path)
{
    Assimp::Importer importer;
    string aipath= path.toStdString();
    const aiScene* scene = importer.ReadFile(aipath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    this->directory = path.mid(0,path.lastIndexOf(QChar('/'))+1);
    this->processNode(scene->mRootNode, scene);
}

void AsModel::processNode(aiNode* node, const aiScene* scene)
{
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshList.append(this->processMesh(mesh, scene));
    }
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }

}

Mesh AsModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
    QVector<Vertex> vertices;
    QVector<GLuint> indices;
    QVector<Texture> textures;

    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        // Positions
        QVector3D posVector(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z);
        // Normals
        QVector3D norVector(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z);

        // Texture Coordinates
        QVector2D vec(0.0f,0.0f);
        if(mesh->mTextureCoords[0])
        {
            vec.setX(mesh->mTextureCoords[0][i].x);
            vec.setY(mesh->mTextureCoords[0][i].y);
        }
        Vertex vertex = {
            {posVector.x(),posVector.y(),posVector.z()},
            {norVector.x(),norVector.y(),norVector.z()},
            {vec.x(),vec.y()}
        };
        vertices.push_back(vertex);
    }
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        QVector<Texture> diffuseMaps = this->loadMaterialTextures
                (material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures += diffuseMaps;
        QVector<Texture> specularMaps = this->loadMaterialTextures
                (material, aiTextureType_SPECULAR, "texture_specular");
        textures += specularMaps;
    }
    return Mesh(vertices, indices, textures);
}

QVector<Texture> AsModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName)
{
    QVector<Texture> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        QString fileName = this->directory+ str.C_Str();
        GLboolean skip = false;
        for(GLuint j = 0; j < texturesLoaded.size(); j++)
        {
            if(texturesLoaded[j].path == fileName)
            {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {
            Texture texture;
            texture.type = typeName;
            texture.path = fileName;
            textures.push_back(texture);
            this->texturesLoaded.push_back(texture);
        }
    }
    return textures;
}
