
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include "TestWidget.hpp"
#include "TestTreeView.hpp"
#include "TableView.hpp"

int main(int argc,char **argv) {

    QApplication app(argc,argv);

    //TestWidget widget ;
    //widget.show();

    //TestTreeView widget;
    //widget.show();

    TableView widget;
    widget.show();

    return app.exec();
}

