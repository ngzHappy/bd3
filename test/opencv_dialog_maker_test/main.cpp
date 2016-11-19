#include "MainWindow.hpp"
#include <QApplication>
#include "XDialog.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    XDialog x;
    x.show();

    MainWindow w;
    w.show();

    return a.exec();
}
