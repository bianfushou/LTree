#include "mscene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::initScene(QOpenGLFunctions_4_3_Core *f, QOpenGLShaderProgram *shader)
{
    if(!pVecMod->model->init)
        pVecMod->model->initModel(f,shader);
    QMap<MPointKey,QList<VecModel*>>::iterator i;
    for(i = this->mapModle.begin();i!=this->mapModle.end();i++)
    {
        for(int k =0;k<i.value().size();k++)
        {
            if(i.value().at(k)->model->init == false)
                i.value().at(k)->model->initModel(f,shader);
        }
    }

}

void Scene::pastVModel(VecModel &model1, VecModel& model2)
{
    model1.f=model2.f;
    model1.model->setMeshList(model2.model->getMeshList());
    model1.model->setTexturesLoaded(model2.model->getTexturesLoaded());
    model1.path = model2.path;
    model1.scale = model2.scale;
}

void Scene::drowScene(QOpenGLFunctions_4_3_Core *f, QMatrix4x4 view, QMatrix4x4 projM)
{
    QMap<MPointKey,QList<VecModel*>>::iterator i;
    for(i = this->mapModle.begin();i!=this->mapModle.end();i++)
    {
        for(int k =0;k<i.value().size();k++)
        {
            i.value().at(k)->model->pMatrix= projM;
            i.value().at(k)->model->vMatrix = view;
            i.value().at(k)->model->drow(f);
        }
    }
    pVecMod->model->pMatrix=projM;
    pVecMod->model->vMatrix = view;
    pVecMod->model->drow(f);
}

void Scene::setIoTex(IoGL *iogl)
{
    QMap<MPointKey,QList<VecModel*>>::iterator i;
    for(i = this->mapModle.begin();i!=this->mapModle.end();i++)
    {
        for(int k =0;k<i.value().size();k++)
        {
            i.value().at(k)->model->ioShader->setfGL(iogl);
        }
    }
    pVecMod->model->ioShader->setfGL(iogl);
}

void Scene::makeSmodel(float x, float z, QString path, float le,float width)
{
    Mesh m;
    QVector<Vertex>* ver = m.getVertex();
    QVector<GLuint>* ind = m.getIndices();
    GLfloat mx = x/2;
    GLfloat mz = z/2;
    GLfloat tx = x/le;
    GLfloat tz = z/width;
    border[0] = QVector3D(-mx,-0.5f,mz);
    border[1] = QVector3D(mx,-0.5f,mz);
    border[2] = QVector3D(mx,-0.5f,-mz);
    border[3] = QVector3D(-mx,-0.5f,-mz);
    Vertex v1 = {
        {-mx,-0.5f,mz},
        {0.0f,1.0f,0.0f},
        {0.0f,0.0f}
    };
    Vertex v2 = {
        {mx,-0.5f,mz},
        {0.0f,1.0f,0.0f},
        {tx,0.0f}
    };
    Vertex v3 = {
        {mx,-0.5f,-mz},
        {0.0f,1.0f,0.0f},
        {tx,tz}
    };
    Vertex v4 = {
        {-mx,-0.5f,-mz},
        {0.0f,1.0f,0.0f},
        {0.0f,tz}
    };
    ver->push_back(v1);
    ver->push_back(v2);
    ver->push_back(v3);
    ver->push_back(v4);
    QVector<GLuint> buf = {
        0,1,2,0,2,3
    };
    *ind += buf;
    QVector<Texture> * mtex = m.getTexture();
    Texture tex = {
        0,QString("texture_diffuse"),path
    };
    mtex->push_back(tex);
    Model smde ;
    smde.addMesh(m);
    smde.setTexturesLoaded(*mtex);

    this->pVecMod= new VecModel(QVector3D(0.0f,-0.5f,0.0f),&smde,1.0f);
}

bool Scene::testBorder(QVector3D p,int & i,int &j,QVector3D &newp)
{
    bool f = false;
    i = -1;
    j = -1;
    if(p.x()>border[1].x())
    {
        i = 1;
        newp.setX(border[1].x());
        f = true;
    }
    else if(p.x()<border[0].x())
    {
        i = 0;
        newp.setX(border[0].x());
        f = true;
    }else{
        newp.setX(p.x());
    }
    if(p.z()>border[0].z())
    {
        j = 0;
        newp.setZ(border[0].z());
        f = true;
    }
    else if(p.z()<border[2].z())
    {
        j = 2;
        newp.setZ(border[2].z());
        f = true;
    }
    else
    {
        newp.setZ(p.z());
    }
    return f;
}

void Scene::setSmodelTex(QVector3D point, float le, float width, QString path)
{
    int k,m;
    QVector3D newpo;
    if(!testBorder(point,k,m,newpo))
    {
        QVector3D bpoint[4] ={
            QVector3D(point.x(),-0.5f+0.000001f,point.z()+width),
            QVector3D(point.x()+le,-0.5f+0.000001f,point.z()+width),
            QVector3D(point.x()+le,-0.5f+0.000001f,point.z()),
            QVector3D(point.x(),-0.5f+0.000001f,point.z())
        };
        QVector3D nextp[4];
        Vertex vert[4];
        for(int i = 0;i<4;i++)
        {
            testBorder(bpoint[i],k,m,nextp[i]);
            vert[i].Position[0] = nextp[i].x();
            vert[i].Position[1] = -0.5f+0.000001f;
            vert[i].Position[2] = nextp[i].z();
            vert[i].Normal[0] = 0.0f;
            vert[i].Normal[1] = 1.0f;
            vert[i].Normal[2] = 0.0f;
        }
        vert[0].TexCoords[0] = 0.0f;
        vert[0].TexCoords[1] = 0.0f;
        vert[1].TexCoords[0] = 1.0f;
        vert[1].TexCoords[1] = 0.0f;
        vert[2].TexCoords[0] = 1.0f;
        vert[2].TexCoords[1] = 1.0f;
        vert[3].TexCoords[0] = 0.0f;
        vert[3].TexCoords[1] = 1.0f;
        Texture tex = {
            0,QString("texture_diffuse"),path
        };
        Mesh mesh;
        QVector<Vertex>* ver = mesh.getVertex();
        QVector<GLuint>* ind = mesh.getIndices();
        QVector<Texture>* text = mesh.getTexture();
        ver->push_back(vert[0]);
        ver->push_back(vert[1]);
        ver->push_back(vert[2]);
        ver->push_back(vert[3]);
        QVector<GLuint> buf = {
            0,1,2,0,2,3
        };
        *ind += buf;
        text->push_back(tex);
        this->pVecMod->model->addMesh(mesh);
    }
}

void Scene::addModel(Model *model, QVector3D vec,GLfloat scale)
{
    if(model->getMeshList().size()>0)
    {
        MPointKey key = MPointKey::makePoint(vec.x(),vec.z());
        VecModel* value =new VecModel(vec,model,scale);
        model->mMatrix = value->model->mMatrix;
        delete value->model;
        value->model = model;
        if(this->mapModle.contains(key))
            this->mapModle[key].push_back(value);
        else
        {
            QList<VecModel*> vl = {
                value
            };
            this->mapModle.insert(key,vl);
        }
    }
}

void Scene::delModel(QVector3D vec ,bool& del)
{
    del = false;
    GLfloat r = qSqrt(2.0*2.0);
    MPointKey point = MPointKey::makePoint(vec.x(),vec.z());
    int x = point.x()-1;
    int z = point.z()+1;
    QList<MPointKey> pList;
    for(int i = 0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
           MPointKey bP(x+j,z-i);
           if(bP.testDis(vec,r))
           {
               pList.append(bP);
           }
        }
    }
    int n = pList.size();
    SKeyVal bskv;
    GLfloat pdis = 3.0f;
    bool take=false;
    for(int i =0;i<n;i++)
    {
        bool find = false;
        float dist = 3.1f;
        SKeyVal val = findModel(pList[i],vec,r,dist,find);
        if(find)
        {
            if(pdis>dist)
            {
                take = true;
                bskv = val;
                pdis = dist;
            }
        }
    }
    if(take)
    {
        this->mapModle[bskv.key].removeAt(bskv.i);
        del = true;
    }
}

VecModel Scene::findModel(QVector3D vec, GLfloat r,bool& find)
{

}

SKeyVal Scene::findModel(MPointKey key,QVector3D vec,GLfloat r,GLfloat& d,bool &find)
{
    if(!(this->mapModle.contains(key)))
    {
        SKeyVal pd;
        find = false;
        return pd;
    }
    QList<VecModel*> vmodel = this->mapModle[key];
    VecModel* bmodel;
    int index;
    find = false;
    for(int i = 0; i<vmodel.size();i++)
    {
        GLfloat kr = vmodel[i]->f.distanceToPoint(vec);
        if(kr<r)
        {
            if(!find)
            {
                bmodel = vmodel[i];
                index = i;
                d = kr;
                find =true;
            }
            else
            {
                if(bmodel->f.distanceToPoint(vec)>kr)
                {
                    index = i;
                    d = kr;
                    bmodel = vmodel[i];
                }
            }
        }
    }
    if(find)
    {
        SKeyVal skv;
        skv.i = index;
        skv.key = key;
        skv.model = bmodel;
        return skv;
    }
    SKeyVal p;
    return p;
}
