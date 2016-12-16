#include "treecontrol.h"
#include "io/iomodel.h"
#include "model/model.h"
#include "lf/lf2.h"
#include "window/treedesign.h"

#define N 100

treeControl::treeControl()
{

}

Model* treeControl::tree2Model(QJsonObject configJson)
{
    GLfloat r1,r2,a0,a2,d,wr,wa,minWa,l;
    if(treeJson(r1,r2,a0,a2,d,wr,wa,minWa,l,configJson))
    {
        Tree2 tree(wa,minWa,l,r1,r2,a0,a2,d,wr);
        if(tree.testTree())
        {
            tree.bulidTree(false);
            return tree.bulidModel();
        }
    }
    return 0;
}

bool treeControl::treeJson(GLfloat &r1, GLfloat &r2, GLfloat &a0, GLfloat &a2, GLfloat &d, GLfloat &wr,
                           GLfloat &wa, GLfloat &minWa, GLfloat &l,QJsonObject& configJson)
{
    bool test = false;
    int k = 0;
    QJsonValue jr1 = configJson.value(QString("r1"));
    if(!jr1.isUndefined())
    {
        r1=(GLfloat)jr1.toDouble();
        k++;
    }
    QJsonValue jr2 = configJson.value(QString("r2"));
    if(!jr2.isUndefined())
    {
        r2=(GLfloat)jr2.toDouble();
        k++;
    }
    QJsonValue ja0 = configJson.value(QString("a0"));
    if(!ja0.isUndefined())
    {
        a0=(GLfloat)ja0.toDouble();
        k++;
    }
    QJsonValue ja2 = configJson.value(QString("a2"));
    if(!ja2.isUndefined())
    {
        a2=(GLfloat)ja2.toDouble();
        k++;
    }
    QJsonValue jd = configJson.value(QString("d"));
    if(!jd.isUndefined())
    {
        d=(GLfloat)jd.toDouble();
        k++;
    }
    QJsonValue jwr = configJson.value(QString("wr"));
    if(!jwr.isUndefined())
    {
        wr=(GLfloat)jwr.toDouble();
        k++;
    }
    QJsonValue jwa = configJson.value(QString("wa"));
    if(!jwa.isUndefined())
    {
        wa=(GLfloat)jwa.toDouble()/N;
        k++;
    }
    QJsonValue jminWa = configJson.value(QString("minWa"));
    if(!jminWa.isUndefined())
    {
        minWa=(GLfloat)jminWa.toDouble()/N;
        k++;
    }
    QJsonValue jl = configJson.value(QString("l"));
    if(!jl.isUndefined())
    {
        l=(GLfloat)jl.toDouble()/N;
        k++;
    }
    if(k==9)
    {
        test = true;
    }
    return test;
}

//json.insert("lpath",ui->lineEdit_l1->text());
//json.insert("lh",ui->lineEdit_l2->text().toDouble());
//json.insert("lwa",ui->lineEdit_l3->text().toDouble());
//json.insert("lshininess",ui->lineEdit_l4->text().toInt());
//json.insert("lminw",ui->lineEdit_l5->text().toDouble());

bool treeControl::treeTexJson(QString& path,GLfloat& wa,GLfloat& h,int &shininess,GLfloat& minw,
                              QString f,QJsonObject& configJson)
{
    QString spath =f+"path";
    QString sh =f+"h";
    QString swa =f+"wa";
    QString sminw =f+"minw";
    QString sshininess =f+"shininess";
    bool test = false;
    int k = 0;

    QJsonValue jpath = configJson.value(spath);
    if(!jpath.isUndefined())
    {
        path= jpath.toString();
        k++;
    }
    QJsonValue jh = configJson.value(sh);
    if(!jh.isUndefined())
    {
        h=(GLfloat)jh.toDouble();
        k++;
    }
    QJsonValue jwa = configJson.value(swa);
    if(!jwa.isUndefined())
    {
        wa=(GLfloat)jwa.toDouble();
        k++;
    }
    QJsonValue jminWa = configJson.value(sminw);
    if(!jminWa.isUndefined())
    {
        minw=(GLfloat)jminWa.toDouble();
        k++;
    }
    QJsonValue jshininess = configJson.value(sshininess);
    if(!jshininess.isUndefined())
    {
        shininess=(GLfloat)jshininess.toInt();
        k++;
    }
    if(k == 5)
    {
        test = true;
    }
    return test;
}

QList<QVector<Texture>> loadTex(QString mpath,QString vpath,QString lpath)
{
    Texture mtex1,mtex2;
    mtex1.type = "texture_diffuse";
    mtex2.type = "texture_specular";
    mtex1.path = mpath;
    mtex2.path = mpath;
    QVector<Texture> mtextu ={
        mtex1,mtex2
    };
    Texture vtex1,vtex2;
    vtex1.type = "texture_diffuse";
    vtex2.type = "texture_specular";
    vtex1.path = vpath;
    vtex2.path = vpath;
    QVector<Texture> vtextu ={
        vtex1,vtex2
    };
    Texture ltex1,ltex2;
    ltex1.type = "texture_diffuse";
    ltex2.type = "texture_specular";
    ltex1.path = lpath;
    ltex2.path = lpath;
    QVector<Texture> ltextu ={
        ltex1,ltex2
    };
    QList<QVector<Texture>> textureload =
    {
      mtextu,vtextu,ltextu
    };
    return textureload;
}

Model* treeControl::tree2TexModel(QJsonObject configJson)
{
    GLfloat r1,r2,a0,a2,d,wr,wa,minWa,l;
    IoModel* ioModel = IoModel::getIo();
    QJsonObject copyjson = ioModel->getCopyjson();
    if(!treeJson(r1,r2,a0,a2,d,wr,wa,minWa,l,copyjson))
    {
        return 0;
    }
    Tree2 tree(wa,minWa,l,r1,r2,a0,a2,d,wr);
    if(!tree.testTree())
    {
        return 0;
    }
    QString mpath,vpath,lpath;
    GLfloat mwa,mh,mminw,vwa,vh,vminw,lwa,lh,lminw;
    int mshininess,vshininess,lshininess;
    if(
            treeTexJson(mpath,mwa,mh,mshininess,mminw,QString("m"),configJson) &&
            treeTexJson(vpath,vwa,vh,vshininess,vminw,QString("v"),configJson) &&
            treeTexJson(lpath,lwa,lh,lshininess,lminw,QString("l"),configJson))
    {

        tree.setTexturesLoaded(loadTex(mpath,vpath,lpath));

        TexTree texTree =
        {
            {mminw/N,vminw/N},
            {
                {lf2::numTexID(mwa/N),1},
                {lf2::numTexID(vwa/N),1},
                {lf2::numTexID(lwa/N),1}
            },
            {
                1.0f/mh*N,
                1.0f/vh*N,
                1.0f/lh*N
            },
            {
                {QVector2D(0.0f,0.0f),QVector2D(1.0f,0.0f),QVector2D(0.0f,1.0f),QVector2D(1.0f,1.0f)},
                {QVector2D(0.0f,0.0f),QVector2D(1.0f,0.0f),QVector2D(0.0f,1.0f),QVector2D(1.0f,1.0f)},
                {QVector2D(0.0f,0.0f),QVector2D(1.0f,0.0f),QVector2D(0.0f,1.0f),QVector2D(1.0f,1.0f)}
            }
        };
        tree.setTexTree(texTree);
        tree.bulidTree(true);
        return tree.bulidModel();
    }

    return 0;
}
