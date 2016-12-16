/********************************************************************************
** Form generated from reading UI file 'asmodel.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASMODEL_H
#define UI_ASMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include "window/asmodelshow.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsModel
{
public:
    AsmodelShow *openGLWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *AsModel)
    {
        if (AsModel->objectName().isEmpty())
            AsModel->setObjectName(QStringLiteral("AsModel"));
        AsModel->resize(751, 463);
        openGLWidget = new AsmodelShow(AsModel);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(20, 40, 691, 421));
        widget = new QWidget(AsModel);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 10, 671, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        retranslateUi(AsModel);

        QMetaObject::connectSlotsByName(AsModel);
    } // setupUi

    void retranslateUi(QWidget *AsModel)
    {
        AsModel->setWindowTitle(QApplication::translate("AsModel", "Form", 0));
        label->setText(QApplication::translate("AsModel", "\350\267\257\345\276\204\357\274\232", 0));
        pushButton->setText(QApplication::translate("AsModel", "\346\230\276\347\244\272", 0));
        pushButton_2->setText(QApplication::translate("AsModel", "\344\277\235\345\255\230", 0));
    } // retranslateUi

};

namespace Ui {
    class AsModel: public Ui_AsModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASMODEL_H

