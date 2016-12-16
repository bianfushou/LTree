#include "window/designwindow.h"
#include "window/treedesign.h"
#include "io/iomodel.h"
#include "mainwindow.h"
#include <QJsonObject>

DesignWindow::DesignWindow(MainWindow *parent):
    QWidget(parent),
    ui(new Ui::Form),
    con(new treeControl),
    model(0)
{
    ui->setupUi(this);
    doubleValidator = new QDoubleValidator(0.0,1.0,6,this);
    douVailAngle = new QDoubleValidator(-180.0,180.0,6,this);
    douVailD = new QDoubleValidator(0.0,360.0,6,this);
    douVailL = new QDoubleValidator(0.0,10000.0,6,this);
    douVailW = new QDoubleValidator(0.01,500.0,6,this);
    ui->lineEdit->setValidator(doubleValidator);
    ui->lineEdit_2->setValidator(doubleValidator);
    ui->lineEdit_3->setValidator(douVailAngle);
    ui->lineEdit_4->setValidator(douVailAngle);
    ui->lineEdit_5->setValidator(douVailD);
    ui->lineEdit_6->setValidator(doubleValidator);
    ui->lineEdit_7->setValidator(douVailW);
    ui->lineEdit_8->setValidator(douVailL);
    ui->lineEdit_9->setValidator(douVailW);
}

DesignWindow::~DesignWindow()
{
    if(this->model != 0)
    {
        delete this->model;
        this->model = 0;
    }
    delete ui;
    delete con;
    delete doubleValidator;
    delete douVailAngle;
    delete douVailD;
    delete douVailL;
    delete douVailW;
}

void DesignWindow::setModel(Model* model)
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
        tree->setHastex(false);
        tree->show();
        tree->setModel(this->model);
    }
}

void DesignWindow::on_pushButton_clicked()
{
    QJsonObject cjson;
    json = cjson;
    json.insert(QString("r1"),QJsonValue(ui->lineEdit->text().toDouble()));
    json.insert(QString("r2"),QJsonValue(ui->lineEdit_2->text().toDouble()));
    json.insert(QString("a0"),QJsonValue(ui->lineEdit_3->text().toDouble()));
    json.insert(QString("a2"),QJsonValue(ui->lineEdit_4->text().toDouble()));
    json.insert(QString("d"),QJsonValue(ui->lineEdit_5->text().toDouble()));
    json.insert(QString("wr"),QJsonValue(ui->lineEdit_6->text().toDouble()));
    json.insert(QString("wa"),QJsonValue(ui->lineEdit_7->text().toDouble()));
    json.insert(QString("l"),QJsonValue(ui->lineEdit_8->text().toDouble()));
    json.insert(QString("minWa"),QJsonValue(ui->lineEdit_9->text().toDouble()));
    setModel(con->tree2Model(json));

    update();
}

void DesignWindow::on_pushButton_2_clicked()
{
    IoModel* ioModel = IoModel::getIo();
    ioModel->setCopyModel(model);
    ioModel->setCopyJson(json);
}
