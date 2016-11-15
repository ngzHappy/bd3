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
public:

    /*构造函数*/
    BasicImageView(const QImage & arg) :BasicImageView(){
        setImage(arg);
    }

    /*默认构造函数*/
    BasicImageView() {
        setMinimumSize(64,64);
    }

    /*析构函数*/
    ~BasicImageView() {

    }

    /*设置图片*/
    void setImage(const QImage & arg) {
        /*获得独立copy*/
        _pm_Image=arg.copy();
        _pm_DrawImage={};
        /*更新显示*/
        update();
    }

    /*获得图片*/
    const QImage & getImage() const {
        /*获得独立拷贝*/
        return _pm_Image;
    }
protected:
    void paintEvent(QPaintEvent *) override {
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
    }
private:
    CPLUSPLUS_OBJECT(BasicImageView)
};

class DockWidget :public QDockWidget{
    using _Super=QDockWidget;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(DockWidget)
};

class MenuBar :public QMenuBar{
    using _Super=QMenuBar;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(QMenuBar)
};

class Menu :public QMenu{
    using _Super= QMenu;
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
    PlainImageView * centralWidget=nullptr;
    ImageChartView * chartCentralWidget=nullptr;
    __private::BasicImageView * originalWidget=nullptr;
    __private::MenuBar * menuBar=nullptr;
    __private::Menu * basicMenu=nullptr;
private:
    CPLUSPLUS_OBJECT(_PrivateImageShowWidget)
};

ImageShowWidget::ImageShowWidget(
        QWidget * var_parent,
        Qt::WindowFlags var_flags):
    Super(var_parent,var_flags) {
    _pm_this_data=new _PrivateImageShowWidget;

    {
        _pm_this_data->menuBar=new __private::MenuBar(this);
        this->setMenuBar(_pm_this_data->menuBar);
        auto varMenu=new __private::Menu;
        varMenu->setTitle(u8R"(基本操作)"_qs);
        _pm_this_data->menuBar->addMenu(varMenu);
        _pm_this_data->basicMenu=varMenu;
    }

    /*设置原始图片*/
    {
        _pm_this_data->originalWidget=new __private::BasicImageView;
        auto varDock=new __private::DockWidget;
        varDock->setWindowTitle(u8R"(原始图片)"_qs);
        varDock->setWidget(_pm_this_data->originalWidget);
        varDock->setAllowedAreas(Qt::AllDockWidgetAreas);
        this->addDockWidget(Qt::LeftDockWidgetArea,varDock);
        _pm_this_data->basicMenu->addAction(varDock->toggleViewAction());
    }

    _pm_this_data->centralWidget=new PlainImageView;
    setCentralWidget(_pm_this_data->centralWidget);
}

ImageShowWidget::~ImageShowWidget() {
    delete _pm_this_data;
}

PlainImageView * ImageShowWidget::setImage(const QImage & arg) {
    /*设置原始图片*/
    _pm_this_data->originalWidget->setImage(arg);
    /*设置显示图片*/
    _pm_this_data->centralWidget=new PlainImageView;
    _pm_this_data->chartCentralWidget=nullptr;
    _pm_this_data->centralWidget->setImage(
        _pm_this_data->originalWidget->getImage(),false);
    setCentralWidget(_pm_this_data->centralWidget);
    return _pm_this_data->centralWidget;
}

ImageChart * ImageShowWidget::setChartImage(
    const QImage & argImage) {
    /*设置原始图片*/
    _pm_this_data->originalWidget->setImage(argImage);
    /*设置显示图片*/
    _pm_this_data->centralWidget=nullptr;
    _pm_this_data->chartCentralWidget=new ImageChartView;
    _pm_this_data->chartCentralWidget->setImage(
        _pm_this_data->originalWidget->getImage(),false);
    setCentralWidget(_pm_this_data->chartCentralWidget);
    return _pm_this_data->chartCentralWidget->imageChart();
}

const QImage &ImageShowWidget::getImage() const {
    /*获得原始图片*/
    return _pm_this_data->originalWidget->getImage();
}

inline ImageShowWidget::_PrivateImageShowWidget::_PrivateImageShowWidget() {

}

inline ImageShowWidget::_PrivateImageShowWidget::~_PrivateImageShowWidget() {

}


