#ifndef DESIGNSCENE_H
#define DESIGNSCENE_H
#include "ui_plane.h"
#include "scenedesign.h"
#include <QWidget>
//#include "designmainwindow.h"

class DesignMainWindow;

namespace Ui {
    class Plan;
}

class DesignScene:public QWidget
{
    Q_OBJECT
public:
    DesignScene(DesignMainWindow *mw=0);
    ~DesignScene();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Plan *ui;
    SceneDesign* scene;
};

#endif // DESIGNSCENE_H
