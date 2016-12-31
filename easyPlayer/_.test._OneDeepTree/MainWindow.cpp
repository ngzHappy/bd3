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

    void paintEvent(QPaintEvent *argEvent) override {
        Super::paintEvent(argEvent);

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|
            QPainter::TextAntialiasing|
            QPainter::SmoothPixmapTransform|
            QPainter::HighQualityAntialiasing
        );

        painter.setBrush(QColor(222,std::rand()&127,std::rand()&127));
        painter.setPen(QPen(QColor(123,222,123),2));
        painter.drawRect(this->rect());
    }
private:
    CPLUSPLUS_OBJECT(TestOneDeepTreeItemWidget)
};

class TestOneDeepTreeDelegate :public  OneDeepTreeDelegate {
    using Super=OneDeepTreeDelegate;
public:
    using Super::Super;

    OneDeepTreeItemWidget *doCreateEditor(
            QWidget *a,
            const QStyleOptionViewItem &b,
            const QModelIndex &c) const override {
        return new TestOneDeepTreeItemWidget(a);
        (void)c; (void)b;
    }
private:
    CPLUSPLUS_OBJECT(TestOneDeepTreeDelegate)
};

}/*namespace*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    auto varView=new OneDeepTreeView;
    auto varDelegate=new TestOneDeepTreeDelegate(varView);
    varView->setItemDelegate(varDelegate);
    this->setCentralWidget(varView);

    /*增加测试数据*/
    auto && model=memory::makeStackPointer<QStandardItemModel>(varView);
    QStandardItem *parentItem=model->invisibleRootItem();

    {
        auto && row=memory::makeStackPointer<QStandardItem>("1234");
        row->setSizeHint({ 32,32 });
        parentItem->appendRow(row.release());
        for (int i=0; i<17; ++i) {
            auto && row1=memory::makeStackPointer<QStandardItem>("1234");
            row1->setSizeHint({ 16,32 });
            row->appendRow(row1.release());
        }
    }

    {
        auto && row=memory::makeStackPointer<QStandardItem>("1234");
        row->setSizeHint({ 32,32 });
        parentItem->appendRow(row.release());
        for (int i=0; i<17; ++i) {
            auto && row1=memory::makeStackPointer<QStandardItem>("1234");
            row1->setSizeHint({ 16,32 });
            row->appendRow(row1.release());
        }
    }

    {
        auto && row=memory::makeStackPointer<QStandardItem>("1234");
        row->setSizeHint({ 32,32 });
        parentItem->appendRow(row.release());
        for (int i=0; i<17; ++i) {
            auto && row1=memory::makeStackPointer<QStandardItem>("1234");
            row1->setSizeHint({ 16,32 });
            row->appendRow(row1.release());
        }
    }

    varView->setModel(model.release());
}

MainWindow::~MainWindow() {

}
