#ifndef ASMODELCONT_H
#define ASMODELCONT_H

#include<QJsonObject>
#include"model/asmodel.h"
#include"model/model.h"

class AsmodelCont
{
public:
    AsmodelCont();
    Model* asmodelCon(QJsonObject json);
private:
    void testAsmodelJson(QString& path,QJsonObject& json);
};

#endif // ASMODELCONT_H
