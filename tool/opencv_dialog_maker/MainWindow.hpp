#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateMainWindow;
    _PrivateMainWindow * thisp;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void _p_get_lua_file();
    void _p_get_out_dir();
    void _p_do_output();
private:
    CPLUSPLUS_OBJECT(MainWindow)
};

#endif // MAINWINDOW_HPP
