#include "ImageChart.hpp"
#include <QtCharts/qvalueaxis.h>
#include <QtGui/qimage.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qpainter.h>
#include <cmath>

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

}/*__private*/
}/*namesapce*/

class ImageChart::_PrivateImageChart {
public:
    QPixmap drawImageCache;
    QImage drawImage;
    QImage oldImage;
    std::shared_ptr<AbstractImageShift> algorithm;
private:
    CPLUSPLUS_OBJECT(_PrivateImageChart)
};

ImageChart::~ImageChart() {
    delete _mp;
}

ImageChart::ImageChart(QGraphicsItem *parent,Qt::WindowFlags wFlags)
    :_Super(parent,wFlags) {
    setBackgroundVisible(false);
    _mp=new _PrivateImageChart;
}

void ImageChart::paint(
    QPainter *painterx,
    const QStyleOptionGraphicsItem *option,
    QWidget *widget) {

    if (_mp->drawImage.isNull()) {
        return  _Super::paint(painterx,option,widget);
    }

    if (_p_update_axis()) {
        /*坐标轴正确*/
        auto varPloatArea=this->plotArea();
        auto varPloatAreaSize=varPloatArea.size().toSize();
        auto & _pm_DrawImage=_mp->drawImageCache;
        const auto & varImage=_mp->drawImage;

        if (varPloatAreaSize!=_pm_DrawImage.size()) {
            _pm_DrawImage=QPixmap::fromImage(varImage.scaled(varPloatAreaSize,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation));
        }

        QPainter & painter=*painterx;
        painter.drawPixmap(varPloatArea.x(),varPloatArea.y(),_pm_DrawImage);

        try {
            const auto varDrawSize=varPloatArea.size();
            const auto varDrawPos=varPloatArea.topLeft();
            if (_mp->algorithm) {
                if (varDrawSize==varImage.size()) {/*只有平移*/
                    painter.save();
                    painter.translate(varDrawPos);
                    try {
                        _mp->algorithm->paint(&painter,varPloatArea.size());
                    }
                    catch (...) { throw; }
                    painter.restore();
                }
                else {
                    const QSizeF oSize=varImage.size();
                    painter.save();
                    painter.translate(varDrawPos);
                    painter.scale(varDrawSize.width()/oSize.width(),
                        varDrawSize.height()/oSize.height());
                    try {
                        _mp->algorithm->paint(&painter,oSize.toSize());
                    }
                    catch (...) { throw; }
                    painter.restore();
                }
            }
        }
        catch (...) {
            CPLUSPLUS_EXCEPTION(false);
        }

    }
    else {
        /*坐标轴有误*/
        const auto & varImage=_mp->drawImage;
        auto & _pm_DrawImage=_mp->drawImageCache;
        if (varImage.isNull()) { return; }
        const auto varSize=this->size().toSize();

        auto varDrawSize=__private::imageResizeSize(
            varImage.size(),varSize);

        if (varDrawSize!=_pm_DrawImage.size()) {
            _pm_DrawImage=QPixmap::fromImage(varImage.scaled(varDrawSize,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation));
        }

        QPainter & painter=*painterx;
        painter.setRenderHints(
            QPainter::HighQualityAntialiasing|
            QPainter::TextAntialiasing|
            QPainter::SmoothPixmapTransform
        );

        QPoint varDrawPos={
            std::max(0,(varSize.width()-varDrawSize.width())/2),
            std::max(0,(varSize.height()-varDrawSize.height())/2)
        };
        painter.drawPixmap(varDrawPos,_pm_DrawImage);

        try {
            if (_mp->algorithm) {
                if (varDrawSize==varImage.size()) {/*只有平移*/
                    painter.save();
                    painter.translate(varDrawPos);
                    try {
                        _mp->algorithm->paint(&painter,varDrawSize);
                    }
                    catch (...) { throw; }
                    painter.restore();
                }
                else {
                    const QSizeF oSize=varImage.size();
                    painter.save();
                    painter.translate(varDrawPos);
                    painter.scale(varDrawSize.width()/oSize.width(),
                        varDrawSize.height()/oSize.height());
                    try {
                        _mp->algorithm->paint(&painter,oSize.toSize());
                    }
                    catch (...) { throw; }
                    painter.restore();
                }
            }
        }
        catch (...) {
            CPLUSPLUS_EXCEPTION(false);
        }

    }

    _Super::paint(painterx,option,widget);
}

void ImageChart::setImage(const QImage &arg,bool _copy) {
    if (_copy) {
        _mp->oldImage=arg.copy();
    }
    else {
        _mp->oldImage=arg;
    }
    _p_alg_or_img_changed();
    update();
    imageChanged();
}

void ImageChart::_p_set_alg(std::shared_ptr<AbstractImageShift>arg) {
    if (arg==_mp->algorithm) { return; }
    _mp->algorithm=std::move(arg);
    _p_alg_or_img_changed();
    update();
    algorithmChanged();
}

const QImage &ImageChart::getAlgorithmImage()const {
    return _mp->drawImage;
}

const std::shared_ptr<AbstractImageShift>&
ImageChart::getAlgorithm()const {
    return _mp->algorithm;
}

const QImage &ImageChart::getImage()const {
    return _mp->oldImage;
}

void ImageChart::_p_alg_or_img_changed() {
    _mp->drawImage={};
    _mp->drawImageCache={};

    try {
        if (_mp->algorithm) {
            _mp->drawImage=
                _mp->algorithm->run(_mp->oldImage);
        }
        else {
            _mp->drawImage=_mp->oldImage;
        }
    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }

}

bool ImageChart::_p_update_axis() {

    const auto & varDrawImage=_mp->drawImage;

    double varIWidth=varDrawImage.width();
    double varIHeight=varDrawImage.height();

    if (varIWidth<0.5) { return false; }
    if (varIHeight<0.5) { return false; }

    auto varAxisX=this->imageXAxis();
    auto varAxisY=this->imageYAxis();

    if (varAxisX&&varAxisY) {

        if ((varAxisX->min()==0)&&(0==varAxisY->min())) {
            if (std::abs(varAxisX->max()-varIWidth)<0.5) {
                if (std::abs(varAxisY->max()-varIHeight)<0.5) {
                    varAxisY->setReverse(true);
                    return true;
                }
            }
        }

        varAxisX->setRange(0,varIWidth);
        varAxisY->setRange(0,varIHeight);
        varAxisY->setReverse(true);
        return true;

    }

    return false;
}



