#ifndef IOMODEL_H
#define IOMODEL_H
#include"model/model.h"
#include"model/mscene.h"

//extern QList<Model*> listModel;
class IoModel
{
public:
    ~IoModel();
    static IoModel* getIo();
    Model* pasteModel();
    void setCopyModel(Model* cModel);
    void setCopyModel(Model* cModel,QMatrix4x4 pm);
    void setCopyJson(QJsonObject copyjson);
    void setTexJson(QJsonObject texjson);
    QJsonObject getCopyjson();
    QJsonObject getTexjson();
    float scale;
private:
    IoModel();
    static IoModel* ioModel;
    Model* copyModel;
    QJsonObject copyjson;
    QJsonObject texjson;

};

#endif // IOMODEL_H
