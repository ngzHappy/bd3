#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtWidgets/qmainwindow.h>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_HPP
