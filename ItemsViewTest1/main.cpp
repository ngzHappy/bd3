#include "TreeView.hpp"
#include "TreeViewItemModel.hpp"
#include <QtWidgets/qapplication.h>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    TreeView view;
    view.show();

    auto * model = view.getItemsModel();

    {
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

    return app.exec();
}



