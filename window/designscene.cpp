#include "designscene.h"
#include "designmainwindow.h"

DesignScene::DesignScene(DesignMainWindow *mw):
    QWidget(mw),ui(new Ui::Plan),scene(0)
{
    ui->setupUi(this);
//    connect(ui->pushButton,QPushButton::click,this,DesignScene::on_pushButton_clicked);
//    connect(ui->pushButton_2,QPushButton::click,this,DesignScene::on_pushButton_2_clicked);
}

DesignScene::~DesignScene()
{

}

void DesignScene::on_pushButton_clicked()
{
    confScene cs;
    cs.slen = ui->lineEdit->text().toFloat();
    cs.swid = ui->lineEdit_2->text().toFloat();
    cs.path = ui->lineEdit_3->text();
    cs.tlen = ui->lineEdit_4->text().toFloat();
    cs.twid = ui->lineEdit_5->text().toFloat();
    cs.ligthdir = QVector3D(0.0f,-1.0f,-1.0f);
    if(ui->buttonGroup->checkedId() == 0)
    {
        cs.f = false;
    }
    else{
        cs.f = true;
    }
    scene = new SceneDesign();
    scene->show();
    scene->setConf(cs);
}

void DesignScene::on_pushButton_2_clicked()
{
    int i=0;
    i++;
}
