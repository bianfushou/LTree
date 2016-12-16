#include "iomodel.h"

IoModel::IoModel():
    copyModel(new Model)
{

}
IoModel::~IoModel()
{
    if(copyModel != 0)
        delete copyModel;
    this->ioModel = nullptr;
}

IoModel* IoModel::getIo()
{
    if (ioModel == nullptr)
    {
        QMutex mutex;
        mutex.lock();
        if (ioModel == nullptr)
        {
            ioModel = new IoModel();
        }
        mutex.unlock();
    }

    return ioModel;
}

void IoModel::setCopyModel(Model *cModel)
{

    this->copyModel->setMeshList(cModel->getMeshList());
    this->copyModel->setTexturesLoaded(cModel->getTexturesLoaded());
}

void IoModel::setCopyModel(Model *cModel, QMatrix4x4 pm)
{
    setCopyModel(cModel);
    pm.setColumn(3,QVector4D(0.0f,0.0f,0.0f,1.0f));
    this->copyModel->setMeshModel(pm);
}

void IoModel::setCopyJson(QJsonObject copyjson)
{
    this->copyjson = copyjson;
}

Model* IoModel::pasteModel()
{
    if(this->copyModel ->getMeshList().size()>0)
    {
        Model* md = new Model();
        md->setMeshList(this->copyModel->getMeshList());
        md->setTexturesLoaded(this->copyModel->getTexturesLoaded());
        return md;
    }
    else
        return 0;
}

QJsonObject IoModel::getCopyjson()
{
    return this->copyjson;
}

void IoModel::setTexJson(QJsonObject texjson)
{
    this->texjson = texjson;
}

QJsonObject IoModel::getTexjson()
{
    return this->texjson;
}
