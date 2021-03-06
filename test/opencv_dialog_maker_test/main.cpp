#include "MainWindow.hpp"
#include <QApplication>
#include <QtCore/qdebug.h>
#include "XDialog.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    XDialog x;
    x.show();

    x.connect(&x,&XDialog::valueChanged,
        [](int a,double b,int c) {
        qDebug()<<a<<b<<c;
    });

    MainWindow w;
    w.show();

    return a.exec();
}
