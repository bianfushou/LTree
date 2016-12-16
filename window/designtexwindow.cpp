#include "designtexwindow.h"
#include "io/iomodel.h"
#include "mainwindow.h"
#include <QJsonObject>

DesignTexWindow::DesignTexWindow(MainWindow *parent):
    QWidget(parent),
    ui(new Ui::TexForm),
    con(new treeControl),
    model(0)
{
    ui->setupUi(this);

    douVailM = new QDoubleValidator(0.0,100.0,6,this);
    intVailD = new QIntValidator(0,128,this);
    douVailH = new QDoubleValidator(0.0,700.0,6,this);
    ui->lineEdit_m2->setValidator(douVailH);
    ui->lineEdit_m3->setValidator(douVailM);
    ui->lineEdit_m4->setValidator(intVailD);
    ui->lineEdit_m5->setValidator(douVailM);

    ui->lineEdit_v2->setValidator(douVailH);
    ui->lineEdit_v3->setValidator(douVailM);
    ui->lineEdit_v4->setValidator(intVailD);
    ui->lineEdit_v5->setValidator(douVailM);

    ui->lineEdit_l2->setValidator(douVailH);
    ui->lineEdit_l3->setValidator(douVailM);
    ui->lineEdit_l4->setValidator(intVailD);
    ui->lineEdit_l5->setValidator(douVailM);
}

DesignTexWindow::~DesignTexWindow()
{
    if(this->model != 0)
    {
        delete this->model;
        this->model = 0;
    }
    delete ui;
    delete con;
    delete douVailH;
    delete douVailM;
    delete intVailD;
}

void DesignTexWindow::setModel(Model* model)
{
    if(this->model != 0)
    {
        delete this->model;
        this->model = 0;
    }
    if(model != 0)
    {
        this->model = model;
        TreeDesign *tree = new TreeDesign(0);
        tree->setVertpath("shaderCode/textlf.vert");
        tree->setFragpath("shaderCode/textlf.frag");
        tree->setHastex(true);
        tree->show();
        tree->setModel(this->model);
    }
}


void DesignTexWindow::on_pushButton_clicked()
{
    QJsonObject texJson;
    this->json = texJson;
    json.insert("mpath",ui->lineEdit_m1->text());
    json.insert("mh",ui->lineEdit_m2->text().toDouble());
    json.insert("mwa",ui->lineEdit_m3->text().toDouble());
    json.insert("mshininess",ui->lineEdit_m4->text().toInt());
    json.insert("mminw",ui->lineEdit_m5->text().toDouble());

    json.insert("vpath",ui->lineEdit_v1->text());
    json.insert("vh",ui->lineEdit_v2->text().toDouble());
    json.insert("vwa",ui->lineEdit_v3->text().toDouble());
    json.insert("vshininess",ui->lineEdit_v4->text().toInt());
    json.insert("vminw",ui->lineEdit_v5->text().toDouble());


    json.insert("lpath",ui->lineEdit_l1->text());
    json.insert("lh",ui->lineEdit_l2->text().toDouble());
    json.insert("lwa",ui->lineEdit_l3->text().toDouble());
    json.insert("lshininess",ui->lineEdit_l4->text().toInt());
    json.insert("lminw",ui->lineEdit_l5->text().toDouble());

    setModel(con->tree2TexModel(json));

    update();
}

void DesignTexWindow::on_pushButton_2_clicked()
{
    IoModel* ioModel = IoModel::getIo();
    ioModel->setCopyModel(model);
    ioModel->setTexJson(json);
}

void DesignTexWindow::on_pushButton_3_clicked()
{
    QJsonObject texJson;
    this->json = texJson;
    json.insert("mpath",ui->lineEdit_m1->text());
    json.insert("mh",ui->lineEdit_m2->text().toDouble());
    json.insert("mwa",ui->lineEdit_m3->text().toDouble());
    json.insert("mshininess",ui->lineEdit_m4->text().toInt());
    json.insert("mminw",ui->lineEdit_m5->text().toDouble());

    json.insert("vpath",ui->lineEdit_v1->text());
    json.insert("vh",ui->lineEdit_v2->text().toDouble());
    json.insert("vwa",ui->lineEdit_v3->text().toDouble());
    json.insert("vshininess",ui->lineEdit_v4->text().toInt());
    json.insert("vminw",ui->lineEdit_v5->text().toDouble());


    json.insert("lpath",ui->lineEdit_l1->text());
    json.insert("lh",ui->lineEdit_l2->text().toDouble());
    json.insert("lwa",ui->lineEdit_l3->text().toDouble());
    json.insert("lshininess",ui->lineEdit_l4->text().toInt());
    json.insert("lminw",ui->lineEdit_l5->text().toDouble());
    Model* buModel = con->tree2TexModel(json);
    if(buModel != 0)
    {
        buModel->rebulidModel();
    }
    setModel(buModel);

    update();
}
