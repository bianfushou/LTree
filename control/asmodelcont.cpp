#include "asmodelcont.h"

AsmodelCont::AsmodelCont()
{

}

Model* AsmodelCont::asmodelCon(QJsonObject json)
{
    QString path;
    testAsmodelJson(path,json);
    AsModel* asmodel= new AsModel();
    asmodel->loadModel(path);
    return asmodel;
}

void AsmodelCont::testAsmodelJson(QString &path, QJsonObject &json)
{
    QJsonValue jpath = json.value(QString("aspath"));
    if(!jpath.isUndefined())
    {
        path=jpath.toString();
    }
}
