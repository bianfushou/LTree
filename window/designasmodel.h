#ifndef DESIGNASMODEL_H
#define DESIGNASMODEL_H

#include<QWidget>
#include"io/iomodel.h"
#include"model/model.h"
#include "ui_asmodel.h"
#include "control/asmodelcont.h"
#include "asmodelshow.h"
#include "treedesign.h"
class MainWindow;

namespace Ui {
    class AsModel;
}

class designAsmodel:public QWidget
{
    Q_OBJECT
public:
    designAsmodel(MainWindow *mw=0);
    ~designAsmodel();

    void setTree(TreeDesign* tree);
signals:
    void newModel(Model * model);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void setModel(Model* model);
    Ui::AsModel *ui;
    AsmodelCont *con;
    Model* model;
    QJsonObject json;
    TreeDesign* tree;
};

#endif // DESIGNASMODEL_H
