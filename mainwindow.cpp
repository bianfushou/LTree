#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSize>
#include "treewidget.h"
#include "lsystem.h"
#include "system/openglfunction.h"
#include "testwidget.h"
#include "window/designwindow.h"
#include "window/designtexwindow.h"
#include "window/designasmodel.h"
#include "io/iomodel.h"
#include <QDockWidget>
#include "window/treedesign.h"
#include "designmainwindow.h"
#include "window/designscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tree = new TreeDesign(this);
    this->setCentralWidget(tree);
    tree->setVertpath("shaderCode/textlf.vert");
    tree->setFragpath("shaderCode/textlf.frag");
    tree->setVisible(true);
//    treeWidget* treewidget = new treeWidget(0);
//    treewidget->resize(600,600);
//    treewidget->show();
//    DesignScene* designl = new DesignScene();
//    designl->show();
    DesignWindow* design = new DesignWindow();
    dock1 = new QDockWidget(tr("生成树形"),this);
    dock1->setWidget(design);
    this->addDockWidget(Qt::LeftDockWidgetArea,dock1);
    DesignTexWindow* designtex = new DesignTexWindow();
    dock2 = new QDockWidget(tr("添加纹理"),this);
    dock2->setWidget(designtex);
    this->addDockWidget(Qt::RightDockWidgetArea,dock2);
    designAsmodel* designAs = new designAsmodel();
    designAs->setTree(tree);
    dock3 = new QDockWidget(tr("加载模型"),this);
    dock3->setWidget(designAs);
    this->addDockWidget(Qt::TopDockWidgetArea,dock3);
    connect(ui->action, QAction::triggered, this, MainWindow::onActionTree);
    connect(ui->action_2,QAction::triggered,this,MainWindow::onActionTexTree);
    connect(ui->action_7,QAction::triggered,this,MainWindow::onActionAsmodel);
    connect(ui->actionLl1,QAction::triggered,this,MainWindow::onActionScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resize(const QSize & size)
{
    QMainWindow::resize(size);
}

void MainWindow::onActionTree()
{
    dock1->setVisible(true);
}

void MainWindow::onActionTexTree()
{
    dock2->setVisible(true);
}

void MainWindow::onActionAsmodel()
{
    dock3->setVisible(true);
}

void MainWindow::onActionScene()
{
    DesignMainWindow* des = new DesignMainWindow();
    des->show();
}
