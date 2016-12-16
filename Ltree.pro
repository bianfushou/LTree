#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T23:28:47
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ltree
TEMPLATE = app

INCLUDEPATH += Include/assimp

LIBS += -LD:/Qt/Ltree/lib/ -llibassimp

SOURCES += main.cpp\
        mainwindow.cpp \
    lhead.cpp \
    lf/lf2.cpp \
    lf/lf.cpp \
    model/mesh.cpp \
    testwidget.cpp \
    window/window.cpp \
    model/model.cpp \
    plant/tree2.cpp \
    lf/lf_leaf.cpp \
    model/asmodel.cpp \
    model/treemodel.cpp \
    control/treecontrol.cpp \
    system/openglfunction.cpp \
    window/treedesign.cpp \
    window/designwindow.cpp \
    io/iomodel.cpp \
    model/scene.cpp \
    io/ioshader.cpp \
    io/iogl_textlf.cpp \
    window/designtexwindow.cpp \
    io/iogl.cpp \
    io/iogltextlf.cpp \
    Utils/camera.cpp \
    control/asmodelcont.cpp \
    window/designasmodel.cpp \
    window/asmodelshow.cpp \
    model/vecmodel.cpp \
    model/mpointkey.cpp \
    Utils/mark.cpp \
    designmainwindow.cpp \
    window/scenedesign.cpp \
    window/designscene.cpp

HEADERS  += mainwindow.h \
    lhead.h \
    lsystem.h \
    lf/lf2.h \
    lf/lf.h \
    model/mesh.h \
    shaderCode/shadercode.h \
    testwidget.h \
    Utils/camera.h \
    window/window.h \
    model/model.h \
    plant/tree2.h \
    plant/config.h \
    lf/lf_leaf.h \
    model/asmodel.h \
    model/treemodel.h \
    control/treecontrol.h \
    system/openglfunction.h \
    window/treedesign.h \
    window/designwindow.h \
    io/iomodel.h \
    io/ioshader.h \
    io/iogl_textlf.h \
    window/designtexwindow.h \
    io/iogl.h \
    io/iogltextlf.h \
    control/asmodelcont.h \
    window/designasmodel.h \
    window/asmodelshow.h \
    ui/ui_asmodel.h \
    model/vecmodel.h \
    model/mpointkey.h \
    Utils/mark.h \
    designmainwindow.h \
    window/scenedesign.h \
    window/designscene.h \
    model/mscene.h

FORMS    += mainwindow.ui \
    ui/tree.ui \
    ui/treetex.ui \
    ui/asmodel.ui \
    designmainwindow.ui \
    ui/plane.ui

DISTFILES += \
    shaderCode/lf.vert \
    shaderCode/lf.frag \
    shaderCode/lf.cont \
    shaderCode/lf.eval \
    shaderCode/blf.frag \
    shaderCode/blf.vert \
    shaderCode/textlf.frag \
    shaderCode/textlf.vert

RESOURCES += \
    image.qrc
