/*MainWindow.hpp*/
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <cplusplus_basic.hpp>
#include <QtWidgets/QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void test();
    void test_assert(bool,const char *);
    void testMD5();

private:
    Ui::MainWindow *ui;
private:
    CPLUSPLUS_OBJECT(MainWindow)
};

#endif // MAINWINDOW_HPP

