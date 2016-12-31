#include "MainWindow.hpp"

#include "../OneDeepTree/OneDeepTreeView.hpp"
#include "../OneDeepTree/OneDeepTreeDelegate.hpp"
#include "../OneDeepTree/OneDeepTreeItemWidget.hpp"

#include <QtGui/qpainter.h>
#include <QtGui/qstandarditemmodel.h>

namespace {

class TestOneDeepTreeItemWidget :public OneDeepTreeItemWidget {
    using Super=OneDeepTreeItemWidget;
public:
    using Super::Super;

    void paintEvent(QPaintEvent *argEvent) {
        Super::paintEvent(argEvent);

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing |
            QPainter::TextAntialiasing |
            QPainter::SmoothPixmapTransform |
            QPainter::HighQualityAntialiasing 
        );

        painter.setBrush(Qt::transparent);
        painter.setPen( QPen(QColor(123,222,123),2) );
        painter.drawRect(this->rect());
    }

};

class TestOneDeepTreeDelegate :public  OneDeepTreeDelegate{
    using Super=OneDeepTreeDelegate;
public:
    using Super::Super;

    OneDeepTreeItemWidget *doCreateEditor(
            QWidget *a,
            const QStyleOptionViewItem &b,
            const QModelIndex &c) const override{
        return new TestOneDeepTreeItemWidget(a);
        (void)c;(void)b;
    }
private:
    CPLUSPLUS_OBJECT(TestOneDeepTreeDelegate)
};

}/*namespace*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    auto varView = new OneDeepTreeView;
    auto varDelegate = new OneDeepTreeDelegate(varView);
    varView->setItemDelegate(varDelegate);
    this->setCentralWidget(varView);

    /*增加测试数据*/
    auto && model = memory::makeStackPointer<QStandardItemModel>(varView);
    
    {
        auto && row=memory::makeStackPointer<QStandardItem>();
        model->appendRow(row.release());
    }

    {
        auto && row=memory::makeStackPointer<QStandardItem>();
        model->appendRow(row.release());
    }

    {
        auto && row=memory::makeStackPointer<QStandardItem>();
        model->appendRow(row.release());
    }

    varView->setModel( model.release() );
}

MainWindow::~MainWindow(){

}
