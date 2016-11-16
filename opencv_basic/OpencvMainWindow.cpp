#include "OpencvMainWindow.hpp"
#include "ImageShowWidget.hpp"
#include <QtWidgets/qmdiarea.h>
#include <QtWidgets/qmdisubwindow.h>
#include <QtWidgets/qboxlayout.h>

namespace {
namespace __private {

class MdiArea : public QMdiArea {
    using _Super=QMdiArea;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(MdiArea)
};
class MidSubWindow : public QMdiSubWindow {
    using _Super=QMdiSubWindow;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(MidSubWindow)
};


}/*__private*/
}/*namespace*/

class OpencvMainWindow::_PrivateOpencvMainWindow {
public:
    __private::MdiArea * mdiArea;
private:
    CPLUSPLUS_OBJECT(_PrivateOpencvMainWindow)
};

OpencvMainWindow::OpencvMainWindow(
        QWidget *parent,
        Qt::WindowFlags flags):_Super(parent,flags) {

    _mp=new _PrivateOpencvMainWindow;
    _mp->mdiArea=new __private::MdiArea(this);
    //_mp->mdiArea->setViewMode(QMdiArea::TabbedView);

    auto * varLayout=new QVBoxLayout;
    varLayout->addWidget(_mp->mdiArea);
    this->setLayout(varLayout);
    varLayout->setMargin(0);
    varLayout->setSpacing(0);

    this->setMinimumSize(512,512);

}

OpencvMainWindow::~OpencvMainWindow() {
    delete _mp;
}

QMdiSubWindow * OpencvMainWindow::addWidget(ImageShowWidget*arg) {

    /*将窗口加入管理系统加入*/
    //auto ans=_mp->mdiArea->addSubWindow(
    //    arg,Qt::WindowType::CustomizeWindowHint|
    //    Qt::WindowType::WindowMinMaxButtonsHint|
    //    Qt::WindowType::WindowTitleHint
    //);

    auto ans=_mp->mdiArea->addSubWindow(arg);
    ans->setMinimumSize(2*128,1*128);
    ans->setAttribute(Qt::WA_DeleteOnClose);
    arg->setAttribute(Qt::WA_DeleteOnClose);

    return ans;

}

void OpencvMainWindow::addImage(const QImage &) {

}



