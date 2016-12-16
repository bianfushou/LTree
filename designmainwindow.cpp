#include "designmainwindow.h"
#include "ui_designmainwindow.h"
#include "window/designscene.h"
DesignMainWindow::DesignMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DesignMainWindow)
{
    ui->setupUi(this);
    DesignScene* design = new DesignScene();
    dock1 = new QDockWidget(tr("生成树形"),this);
    dock1->setWidget(design);
    this->addDockWidget(Qt::LeftDockWidgetArea,dock1);
}

DesignMainWindow::~DesignMainWindow()
{
    delete ui;
}
