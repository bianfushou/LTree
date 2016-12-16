#ifndef DESIGNWINDOW_H
#define DESIGNWINDOW_H

#include<QWidget>
#include<QOpenGLWidget>
#include <QLineEdit>

#include "control/treecontrol.h"
#include "ui_tree.h"
#include"treedesign.h"

class MainWindow;

namespace Ui {
    class Form;
}

class DesignWindow:public QWidget
{
    Q_OBJECT
public:
    DesignWindow(MainWindow *mw=0);
    ~DesignWindow();
//protected:
//    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void setModel(Model* model);
    Ui::Form *ui;
    treeControl *con;
    Model* model;
    QJsonObject json;
    QDoubleValidator *doubleValidator;
    QDoubleValidator *douVailAngle ;
    QDoubleValidator *douVailD ;
    QDoubleValidator *douVailL ;
    QDoubleValidator *douVailW ;
};

#endif // DESIGNWINDOW_H
