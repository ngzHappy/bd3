#include "TreeView.hpp"
#include "TreeViewItemModel.hpp"
#include <QtCore/qtimer.h>
#include <QtWidgets/qapplication.h>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    TreeView view;
    view.show();

    auto * model = view.getItemsModel();

    for(int i=0;i<1000;++i){
        QString title("xxxx");
        model->addListData(title,TreeViewItemData::instance());
        model->addListData(title,TreeViewItemData::instance());
        model->addListData(title,TreeViewItemData::instance());
        model->addListData(title,TreeViewItemData::instance());
        model->addListData(title,TreeViewItemData::instance());
    }

    {
        QString title("yyyyy");
        model->addListData(title,TreeViewItemData::instance());
        model->addListData(title,TreeViewItemData::instance());
        model->addListData(title,TreeViewItemData::instance());
        model->addListData(title,TreeViewItemData::instance());
    }

    view.setSelectionMode(QAbstractItemView::ExtendedSelection);

//    QTimer timer;
//    timer.connect(&timer,&QTimer::timeout,
//                  [model](){
//        if(std::rand()&1){
//            model->addListData("aazz",TreeViewItemData::instance());
//        }else{
//            model->addListData("aazz",TreeViewItemData::instance());
//        }
//    });
//    timer.start(500);

    return app.exec();
}



