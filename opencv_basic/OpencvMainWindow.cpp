#include "OpencvMainWindow.hpp"
#include "ImageShowWidget.hpp"
#include "PlainImageView.hpp"
#include <QtGui/qpainter.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qmdiarea.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmdisubwindow.h>
#include "OpencvApplication.hpp"

namespace {
namespace __private {

class MdiArea : public QMdiArea {
    using _Super=QMdiArea;
public:
    using _Super::_Super;
    MdiArea()=default;
protected:
    void paintEvent(QPaintEvent *e)override {
        return QMdiArea::paintEvent(e);
    }

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

class MenuBar :public QMenuBar{
    using _Super=QMenuBar;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(MenuBar)
};

class Menu :public QMenu{
    using _Super=QMenu;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(Menu)
};

class Action :public QAction{
    using _Super=QAction;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(Action)
};

}/*__private*/
}/*namespace*/

namespace {
inline QString operator""_qs(const char *arg,std::size_t n) {
    return QString::fromUtf8(arg, static_cast<int>(n));
}
}/*namespace*/

class OpencvMainWindow::_PrivateOpencvMainWindow {
public:
    __private::MdiArea * mdiArea;
    __private::MenuBar * menuBar;
    __private::Menu *defaultMenu;
    int addImageIndex=0;
private:
    CPLUSPLUS_OBJECT(_PrivateOpencvMainWindow)
};

OpencvMainWindow::OpencvMainWindow(
        QWidget *parent,
        Qt::WindowFlags flags):_Super(parent,flags) {

    _mp=new _PrivateOpencvMainWindow;
    _mp->mdiArea=new __private::MdiArea(this);
  
    //_mp->mdiArea->setViewMode(QMdiArea::TabbedView);

    setCentralWidget(_mp->mdiArea);
    _mp->mdiArea->setTabsMovable(true);
    _mp->mdiArea->setBackground(Qt::transparent);

    this->setMinimumSize(512,512);

    _mp->menuBar=new __private::MenuBar;
    _mp->menuBar->setParent(this);
    this->setMenuBar(_mp->menuBar);

    _mp->defaultMenu=new __private::Menu(this);
    _mp->defaultMenu->setTitle(u8R"(基本操作)"_qs);
    
    {
        auto openaction=new __private::Action(u8R"(层叠窗口)"_qs,this);
        _mp->defaultMenu->addAction(openaction);
        connect(openaction,&QAction::triggered,
            _mp->mdiArea,&QMdiArea::cascadeSubWindows);
    }

    {
        auto openaction=new __private::Action(u8R"(并排窗口)"_qs,this);
        _mp->defaultMenu->addAction(openaction);
        connect(openaction,&QAction::triggered,
            _mp->mdiArea,&QMdiArea::tileSubWindows);
    }

    {
        auto openaction=new __private::Action(u8R"(打开图片)"_qs,this);
        _mp->defaultMenu->addAction(openaction);
        connect(openaction,&QAction::triggered,
            this,&OpencvMainWindow::_p_open_image);
    }

    {
        auto openaction=new __private::Action(u8R"(打开lua)"_qs,this);
        _mp->defaultMenu->addAction(openaction);
        connect(openaction,&QAction::triggered,
            this,&OpencvMainWindow::_p_open_lua);
    }

    _mp->menuBar->addMenu(_mp->defaultMenu);

}

void OpencvMainWindow::_p_open_lua(){

    const auto varImages= QFileDialog::getOpenFileName(this,
        u8R"(打开lua文件)"_qs/*caption*/,
        {}/*dir*/,
        u8R"(lua文件(*.lua *.lua.gz *.gz);;所有类型(*.*))"_qs
        );

    if (varImages.isEmpty()) { return; }

    qApp->readLuaFile(varImages);
    openLua();

}

void OpencvMainWindow::_p_open_image() {

    const auto varImages= QFileDialog::getOpenFileNames(this,
        u8R"(打开图片)"_qs/*caption*/,
        {}/*dir*/,
        u8R"(图片文件(*.png *.jpg *.bmp);;所有类型(*.*))"_qs
        );

    if (varImages.isEmpty()) { return; }

    for (const auto &i:varImages) {
        this->addImage(QImage(i));
    }

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

    ans->setOption(QMdiSubWindow::RubberBandResize,true);
    //ans->setOption(QMdiSubWindow::RubberBandMove,true);

    ans->show();

    return ans;

}

QWidget* OpencvMainWindow::addImage(const QImage & arg) {
    if (addImageIndex()<0) { return nullptr; }
    if (arg.isNull()) { return nullptr; }
    auto var= new ImageShowWidget(this);
    var->setImage(arg);
    return this->addWidget(var);
}

void OpencvMainWindow::addImage(const QPair<const QString *,const QString *>&arg) {
    _AddImageState _{this};
    for (auto i=arg.first;i!=arg.second;++i) {
        auto w=addImage(QImage(*i));
        if (w) { w->setWindowTitle(*i); }
        _p_finished_add_a_image();
    }
}

int OpencvMainWindow::addImageIndex()const {
    return _mp->addImageIndex;
}

void OpencvMainWindow::_p_begin_add_image() {
    _mp->addImageIndex=1;
}

void OpencvMainWindow::_p_end_add_image() {
    _mp->addImageIndex=-1;
    try {
        this->addImage(QImage{});
    }
    catch (...) {
        _mp->addImageIndex=0;
        throw;
    }
    _mp->addImageIndex=0;
}

void OpencvMainWindow::_p_finished_add_a_image() {
    ++_mp->addImageIndex;
}

void OpencvMainWindow::paintEvent(QPaintEvent *) {
    // Background
    static const auto backgroundGradient=[]() {
        QLinearGradient backgroundGradient(0.5,1.0,0.5,0.0);
        backgroundGradient.setColorAt(0.0,QRgb(0x2e303a));
        backgroundGradient.setColorAt(1.0,QRgb(0x121218));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        return std::move(backgroundGradient);
    }();
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|
    QPainter::HighQualityAntialiasing);
    painter.setBrush(backgroundGradient);
    painter.drawRect(this->rect());
}

void OpencvMainWindow::openLua(){
    addImage(qApp->getAllImageNames());
}








