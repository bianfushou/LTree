#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"window/designwindow.h"
#include"window/designtexwindow.h"
#include"window/designasmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resize(const QSize &);
private slots:
    void onActionTree();
    void onActionTexTree();
    void onActionAsmodel();
    void onActionScene();
private:
    bool istree;
    Ui::MainWindow *ui;
    QDockWidget* dock1;
    QDockWidget* dock2;
    QDockWidget* dock3;
    TreeDesign * tree;
};

#endif // MAINWINDOW_H
