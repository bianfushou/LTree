#ifndef DESIGNMAINWINDOW_H
#define DESIGNMAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
namespace Ui {
class DesignMainWindow;
}

class DesignMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DesignMainWindow(QWidget *parent = 0);
    ~DesignMainWindow();

private:
    Ui::DesignMainWindow *ui;
    QDockWidget* dock1;

};

#endif // DESIGNMAINWINDOW_H
