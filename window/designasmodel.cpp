#include "designasmodel.h"
#include "treedesign.h"
#include "mainwindow.h"

designAsmodel::designAsmodel(MainWindow *mw):
    QWidget(mw),
    ui(new Ui::AsModel),
    con(new AsmodelCont),
    model(0)
{
    ui->setupUi(this);
}

designAsmodel::~designAsmodel()
{
    if(this->model != 0)
    {
        delete this->model;
        this->model = 0;
    }
    delete ui;
    delete con;
}

void designAsmodel::setModel(Model *model)
{
    if(this->model != 0)
    {
        delete this->model;
        this->model = 0;
    }
    if(model != 0)
    {
        this->model = model;
        AsmodelShow* asshow = new AsmodelShow;
        asshow->setVertpath("shaderCode/textlf.vert");
        asshow->setFragpath("shaderCode/textlf.frag");
        asshow->show();
        this->model->rebulidModel();
        asshow->setModel(this->model);
    }
}

void designAsmodel::on_pushButton_clicked()
{
    QJsonObject asJson;
    this->json = asJson;
    json.insert("aspath",ui->lineEdit->text());
    setModel(con->asmodelCon(json));
    update();
}

void designAsmodel::setTree(TreeDesign* tree)
{
    this->tree = tree;
}

void designAsmodel::on_pushButton_2_clicked()
{
    IoModel* ioModel = IoModel::getIo();
    ioModel->setCopyModel(model);
}

void designAsmodel::on_pushButton_3_clicked()
{
    this->model->makeTexture(ui->lineEdit_2->text());
    AsmodelShow* asshow = new AsmodelShow;
    asshow->setVertpath("shaderCode/textlf.vert");
    asshow->setFragpath("shaderCode/textlf.frag");
    asshow->show();
    this->model->rebulidModel();
    asshow->setModel(this->model);
}
