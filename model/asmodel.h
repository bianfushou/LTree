#ifndef ASMODEL_H
#define ASMODEL_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

#include<QImage>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

#include "Mesh.h"
#include "model.h"
#include "lsystem.h"
#include "system/openglfunction.h"

class AsModel : public Model
{
public:
    AsModel();
    void loadModel(QString path);

private:
    QString directory;

    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    QVector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName);
};

#endif // ASMODEL_H
