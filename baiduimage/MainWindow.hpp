#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <cplusplus_basic.hpp>
#include <QtWidgets/QMainWindow>

namespace Ui {
class MainWindow;
}

namespace baiduimage {
class DownLoadCallBack :public QObject {
    Q_OBJECT

public:
    Q_SIGNAL void finished(QString);
};
}/*baiduimage*/

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();

public:
    Q_SLOT void setText(QString);

private:
    Q_SLOT void on_doButton_clicked();

private:
    Ui::MainWindow *ui;
    bool _pm_IsDownLoad=false;
private:
    CPLUSPLUS_OBJECT(MainWindow)
};

#endif // MAINWINDOW_HPP
