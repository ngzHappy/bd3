
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include "TestWidget.hpp"

int main(int argc,char **argv){

    QApplication app(argc,argv);

    TestWidget widget ;
    widget.show();

    return app.exec();
}

