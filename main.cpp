#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include "treewidget.h"
#include "system/openglfunction.h"
#include "io/iomodel.h"

QOpenGLFunctions_4_3_Core* OpenGLFunction::f = nullptr;
IoModel* IoModel::ioModel = nullptr;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();
    //treeWidget treewidget ;
    //treewidget.show();
    return a.exec();
}
