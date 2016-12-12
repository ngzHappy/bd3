#include "MainWindow.hpp"
#include <QApplication>

#include <QtCore/qurl.h>
#include <QtQml/qqmlcontext.h>
#include <QtQuick/qquickview.h>

#include "ItemsModel.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //MainWindow window;
    //window.show();

    QQuickView view;
    ItemsModel *model=new ItemsModel(&view);
    view.rootContext()->setContextProperty("itemsModel",model);
     view.setSource(QUrl("qrc:/main.qml"));
     view.setResizeMode( QQuickView::SizeRootObjectToView );
     view.resize(800,600);
    view.show();

    return app.exec();
}







