#ifndef DESIGNTEXWINDOW_H
#define DESIGNTEXWINDOW_H

#include<QWidget>
#include<QOpenGLWidget>
#include <QLineEdit>

#include "control/treecontrol.h"
#include"ui_treetex.h"
#include"treedesign.h"

class MainWindow;

namespace Ui {
    class TexForm;
}
class DesignTexWindow:public QWidget
{
    Q_OBJECT
public:
    DesignTexWindow(MainWindow *mw=0);
    ~DesignTexWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void setModel(Model* model);
    Ui::TexForm *ui;
    treeControl *con;
    Model* model;
    QJsonObject json;
    QDoubleValidator *douVailM ;
    QIntValidator *intVailD ;
    QDoubleValidator *douVailH;
};

#endif // DESIGNTEXWINDOW_H
