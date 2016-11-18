#include "ImageShowWidget.hpp"
#include "PlainImageView.hpp"
#include "ImageChartView.hpp"
#include <cmath>
#include <QtWidgets/qdockwidget.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qmenubar.h>
#include <QtGui/qimage.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qpainter.h>
#include <QtCore/qpointer.h>
#include <private/qimage_p.h>
#include <list>

/*
 * 简易的gui库,不要用于复杂工程
 * BasicImageView : 显示原始图片
 *
 *
*/

namespace {
namespace __private {

inline QSize imageResizeSize(
        const QSize & argImageSize,
        const QSize & argViewSize) {
    /*如果绘图空间足够不必缩放*/
    if (argViewSize.width()>=argImageSize.width()) {
        if (argViewSize.height()>=argImageSize.height()) {
            return argImageSize;
        }
    }

    /*不合理值*/
    if (argViewSize.width()<=0) { return{ 0,0 }; }
    if (argViewSize.height()<=0) { return{ 0,0 }; }
    if (argImageSize.width()<=0) { return{ 0,0 }; }
    if (argImageSize.height()<=0) { return{ 0,0 }; }

    typedef double eval_float_type;

    const auto varImageWidth=static_cast<eval_float_type>(argImageSize.width());
    const auto varImageHeight=static_cast<eval_float_type>(argImageSize.height());
    const auto varViewWidth=static_cast<eval_float_type>(argViewSize.width());
    const auto varViewHeight=static_cast<eval_float_type>(argViewSize.height());

    /*计算比例*/
    const auto v=varViewWidth/varViewHeight;
    const auto i=varImageWidth/varImageHeight;

    /*如果比例一致*/
    if (v==i) {
        return argViewSize;
    }

    if (i>v) {
        /*image图片宽了*/
        auto h=(varViewWidth/varImageWidth)*varImageHeight;
        QSize ans{
            argViewSize.width(),
            static_cast<decltype(argViewSize.width())>(std::round(h))
        };
        return ans;
    }
    else {
        /*图片窄了*/
        auto w=(varViewHeight/varImageHeight)*varImageWidth;
        QSize ans{
            static_cast<decltype(argViewSize.height())>(std::round(w)),
            argViewSize.height()
        };
        return ans;
    }

}


class BasicImageView :public QWidget {
    QImage _pm_Image;
    QPixmap _pm_DrawImage;
    using _Super=QWidget;
public:

    /*构造函数*/
    BasicImageView(QImage && arg):BasicImageView() {
        setImage(std::move(arg));
    }

    /*默认构造函数*/
    BasicImageView() {
        setMinimumSize(64,64);
    }

    /*析构函数*/
    ~BasicImageView() {

    }

    /*设置图片*/
    void setImage(QImage && arg) {
        /*获得独立copy*/
        _pm_Image=std::move(arg);
        _pm_DrawImage={};
        /*更新显示*/
        update();
    }

    /*获得图片*/
    const QImage & getImage() const {
        /*获得独立拷贝*/
        return _pm_Image;
    }

    QSize sizeHint() const override {
        return{ 128,128 };
    }

protected:

    virtual bool event(QEvent *e) override {
        return _Super::event(e);
    }

    void paintEvent(QPaintEvent *e) override {
        const auto & varImage=_pm_Image;
        if (varImage.isNull()) { return; }
        auto varDrawSize=imageResizeSize(varImage.size(),this->size());
        if (varDrawSize==_pm_DrawImage.size()) {
            QPainter painter(this);
            painter.setRenderHints(
                QPainter::HighQualityAntialiasing|
                QPainter::TextAntialiasing|
                QPainter::SmoothPixmapTransform
            );
            painter.drawPixmap(
                std::max(0,(this->size().width()-varDrawSize.width())/2),
                std::max(0,(this->size().height()-varDrawSize.height())/2),
                _pm_DrawImage);
        }
        else {
            _pm_DrawImage=QPixmap::fromImage(varImage.scaled(varDrawSize,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation));
            QPainter painter(this);
            painter.setRenderHints(
                QPainter::HighQualityAntialiasing|
                QPainter::TextAntialiasing|
                QPainter::SmoothPixmapTransform
            );
            painter.drawPixmap(
                std::max(0,(this->size().width()-varDrawSize.width())/2),
                std::max(0,(this->size().height()-varDrawSize.height())/2),
                _pm_DrawImage);
        }
        return _Super::paintEvent(e);
    }
private:
    CPLUSPLUS_OBJECT(BasicImageView)
};

class DockWidget :public QDockWidget {
    using _Super=QDockWidget;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(DockWidget)
};

class MenuBar :public QMenuBar {
    using _Super=QMenuBar;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(QMenuBar)
};

class Menu :public QMenu {
    using _Super=QMenu;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(Menu)
};

}/**/

inline QString operator""_qs(const char * arg,std::size_t n) {
    return QString::fromUtf8(arg,static_cast<int>(n));
}

}/**/

class ImageShowWidget::_PrivateImageShowWidget {
public:
    inline _PrivateImageShowWidget();
    inline virtual ~_PrivateImageShowWidget();
public:
    QPointer<PlainImageView> centralWidget;
    QPointer<ImageChartView> chartCentralWidget;
    __private::BasicImageView * originalWidget=nullptr;
    QDockWidget * dockOriginalWidget=nullptr;
    __private::MenuBar * menuBar=nullptr;
    __private::Menu * basicMenu=nullptr;
    ImageShowWidget * super;
    std::shared_ptr<AbstractImageShift> algorithm;
    using list_connections_t=std::list<QMetaObject::Connection,memory::Allocator<QMetaObject::Connection>>;
    list_connections_t connections;

    void disconnect() {
        for (const auto & i:connections) {
            super->disconnect(i);
        }
        connections.clear();
    }

#define ONLY_TOP 1
#if  ((ONLY_TOP)<1)
    int currentDock=-1;
    int nextDock() {
        ++currentDock;
        if (currentDock>=4) { currentDock=0; }
        return currentDock;
    }
#endif
    Qt::DockWidgetArea nextArea() {
#if  ((ONLY_TOP)>=0)
        return Qt::DockWidgetArea::TopDockWidgetArea;
#else
        switch (nextDock()) {
            case 0:return Qt::DockWidgetArea::LeftDockWidgetArea;
            case 1:return Qt::DockWidgetArea::BottomDockWidgetArea;
            case 2:return Qt::DockWidgetArea::RightDockWidgetArea;
            case 3:return Qt::DockWidgetArea::TopDockWidgetArea;
        }
        return Qt::DockWidgetArea::LeftDockWidgetArea;
#endif
    }
private:
    CPLUSPLUS_OBJECT(_PrivateImageShowWidget)
};

ImageShowWidget::ImageShowWidget(
        QWidget * var_parent,
        Qt::WindowFlags var_flags):
    Super(var_parent,var_flags) {
    _pm_this_data=new _PrivateImageShowWidget;
    _pm_this_data->super=this;

    {
        _pm_this_data->menuBar=new __private::MenuBar(this);
        this->setMenuBar(_pm_this_data->menuBar);
        auto varMenu=new __private::Menu;
        varMenu->setTitle(u8R"(视图)"_qs);
        _pm_this_data->menuBar->addMenu(varMenu);
        _pm_this_data->basicMenu=varMenu;
    }

    /*设置原始图片*/
    {
        _pm_this_data->originalWidget=new __private::BasicImageView;
        auto varDock=new __private::DockWidget;
        _pm_this_data->originalWidget->setParent(varDock);
        varDock->setParent(this);
        varDock->setWidget(_pm_this_data->originalWidget);
        varDock->setAllowedAreas(Qt::AllDockWidgetAreas);
        this->addDockWidget(
            _pm_this_data->nextArea(),
            varDock);
        _pm_this_data->basicMenu->addAction(varDock->toggleViewAction());
        varDock->setWindowTitle(u8R"(原始图片)"_qs);
        _pm_this_data->dockOriginalWidget=varDock;
    }

    _pm_this_data->centralWidget=new PlainImageView;
    setCentralWidget(_pm_this_data->centralWidget);
    this->setDockNestingEnabled(true);
}

QDockWidget* ImageShowWidget::_p_addImageWidget(
    QWidget*arg,Qt::DockWidgetArea darea,const QString &argTitle) {
    if (arg==nullptr) { return nullptr; }
    {
        auto varDock=new __private::DockWidget;
        arg->setParent(varDock);
        varDock->setParent(this);
        varDock->setWindowTitle(argTitle);
        varDock->setWidget(arg);
        varDock->setAllowedAreas(Qt::AllDockWidgetAreas);
        this->addDockWidget(
            darea,
            varDock);
        _pm_this_data->basicMenu->addAction(
            varDock->toggleViewAction());
        return varDock;
    }
}

QDockWidget* ImageShowWidget::addImageWidget(
    QWidget*arg,const QString &argTitle) {
    return _p_addImageWidget(arg,
        _pm_this_data->nextArea(),argTitle);
}

const std::shared_ptr<AbstractImageShift>&ImageShowWidget::getAlgorithm()const {
    return _pm_this_data->algorithm;
}

void ImageShowWidget::_p_setAlgorithm(const std::shared_ptr<AbstractImageShift>&arg) {
    if (_pm_this_data->chartCentralWidget) {
        _pm_this_data->chartCentralWidget->setAlgorithm(arg);
    }
    else if (_pm_this_data->centralWidget) {
        _pm_this_data->centralWidget->setAlgorithm(arg);
    }
}

void ImageShowWidget::_p_setAlgorithm(std::shared_ptr<AbstractImageShift>&&arg) {
    if (_pm_this_data->chartCentralWidget) {
        _pm_this_data->chartCentralWidget->setAlgorithm(std::move(arg));
    }
    else if (_pm_this_data->centralWidget) {
        _pm_this_data->centralWidget->setAlgorithm(std::move(arg));
    }
}

ImageShowWidget::~ImageShowWidget() {
    delete _pm_this_data;
}

QtCharts::QChartView * ImageShowWidget::setChartView(QtCharts::QChartView *arg) {
    _pm_this_data->disconnect();
    if (arg==nullptr) { return nullptr; }
    _pm_this_data->originalWidget->setImage(QImage{});
    setOriginalImageWidgetVisible(false);
    setCentralWidget(arg);
    emit centralWidgetDataChanged();
    return arg;
}

PlainImageView * ImageShowWidget::setImage(const QImage & arg) {
    _pm_this_data->disconnect();
    /*设置原始图片*/
    if (const_cast<QImage&>(arg).data_ptr()->own_data==false) {
        _pm_this_data->originalWidget->setImage(arg.copy());
    }
    else {
        QImage tmp(arg);
        _pm_this_data->originalWidget->setImage(std::move(tmp));
    }
    /*设置显示图片*/
    _pm_this_data->centralWidget=new PlainImageView;
    _pm_this_data->chartCentralWidget=nullptr;
    _pm_this_data->centralWidget->setImage(
        _pm_this_data->originalWidget->getImage(),false);
    _pm_this_data->centralWidget->setAlgorithm(_pm_this_data->algorithm);
    emit centralWidgetDataChanged();
    _pm_this_data->connections.push_back(
    connect(_pm_this_data->centralWidget,&PlainImageView::imageChanged,
        this,&ImageShowWidget::centralWidgetDataChanged));
    _pm_this_data->connections.push_back(
    connect(_pm_this_data->centralWidget,&PlainImageView::algorithmChanged,
        this,&ImageShowWidget::centralWidgetDataChanged));
    setCentralWidget(_pm_this_data->centralWidget);
    return _pm_this_data->centralWidget;
}

ImageChart * ImageShowWidget::setChartImage(
    const QImage & argImage) {
    _pm_this_data->disconnect();
        {
            /*设置原始图片*/
            auto vardt=const_cast<QImage&>(argImage).data_ptr();
            if (vardt->own_data==false) {
                _pm_this_data->originalWidget->setImage(argImage.copy());
            }
            else {
                QImage tmp(argImage);
                _pm_this_data->originalWidget->setImage(std::move(tmp));
            }
        }
        /*设置显示图片*/
        _pm_this_data->centralWidget=nullptr;
        _pm_this_data->chartCentralWidget=new ImageChartView;
        _pm_this_data->chartCentralWidget->setImage(
            _pm_this_data->originalWidget->getImage(),false);
        _pm_this_data->chartCentralWidget->setAlgorithm(_pm_this_data->algorithm);
        emit centralWidgetDataChanged();
        _pm_this_data->connections.push_back(
        connect(_pm_this_data->chartCentralWidget,&ImageChartView::imageChanged,
            this,&ImageShowWidget::centralWidgetDataChanged));
        _pm_this_data->connections.push_back(
        connect(_pm_this_data->chartCentralWidget,&ImageChartView::algorithmChanged,
            this,&ImageShowWidget::centralWidgetDataChanged));
        setCentralWidget(_pm_this_data->chartCentralWidget);
        return _pm_this_data->chartCentralWidget->imageChart();
}

const QImage &ImageShowWidget::getImage() const {
    /*获得原始图片*/
    return _pm_this_data->originalWidget->getImage();
}

static memory::StaticData<QImage> _d_null;
const QImage &ImageShowWidget::getAlgorithmImage()const {
    if (_pm_this_data->centralWidget) {
        return _pm_this_data->centralWidget->getAlgorithmImage();
    }
    else if(_pm_this_data->chartCentralWidget){
        return _pm_this_data->chartCentralWidget->getAlgorithmImage();
    }
    const static QImage null__;
    static memory::StaticPoionter<QImage> _null__(_d_null);
    return *_null__;
}

inline ImageShowWidget::_PrivateImageShowWidget::_PrivateImageShowWidget() {

}

inline ImageShowWidget::_PrivateImageShowWidget::~_PrivateImageShowWidget() {

}

void ImageShowWidget::setOriginalImageWidgetVisible(bool arg) {
    _pm_this_data->dockOriginalWidget->setVisible(arg);
}



