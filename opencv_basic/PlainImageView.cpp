﻿#include "PlainImageView.hpp"
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

class PlainImageView::_PrivatePlainImageView {
public:
    QImage old_image;
    QImage imageToDraw;
    QPixmap drawImage;
    std::shared_ptr<AbstractImageShift> alg;
    bool isAlgUpdated=false;
private:
    CPLUSPLUS_OBJECT(_PrivatePlainImageView)
};

PlainImageView::PlainImageView() {
    _pm=new _PrivatePlainImageView;
    this->setMinimumSize(64,64);
}

PlainImageView::~PlainImageView() {
    delete _pm;
}

void PlainImageView::paintEvent(QPaintEvent *) {
    const auto & varImage=_pm->imageToDraw;
    auto & _pm_DrawImage=_pm->drawImage;
    if (varImage.isNull()) { return; }
    auto varDrawSize=__private::imageResizeSize(varImage.size(),this->size());
      
    if (varDrawSize!=_pm_DrawImage.size()) {
        _pm_DrawImage=QPixmap::fromImage(varImage.scaled(varDrawSize,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation));
    }

    QPainter painter(this);
    painter.setRenderHints(
        QPainter::HighQualityAntialiasing|
        QPainter::TextAntialiasing|
        QPainter::SmoothPixmapTransform|
        QPainter::Antialiasing
    );

    QPoint varDrawPoint{
        std::max(0,(this->size().width()-varDrawSize.width())/2),
        std::max(0,(this->size().height()-varDrawSize.height())/2)
    };
    painter.drawPixmap(varDrawPoint,_pm_DrawImage);

    try {
        if (_pm->alg) {
            if (varDrawSize==_pm->old_image.size()) {/*只有平移*/
                painter.translate(varDrawPoint);
                _pm->alg->paint(&painter,varDrawSize);
            }
            else {
                const QSizeF oSize=_pm->old_image.size();
                painter.translate(varDrawPoint);
                painter.scale(varDrawSize.width()/oSize.width(),
                    varDrawSize.height()/oSize.height());
                _pm->alg->paint(&painter,oSize.toSize());
            }
        }
    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }

}

void PlainImageView::setImage(const QImage & arg,bool _copy) {
    _pm->isAlgUpdated=false;
    if (_copy) {
        _pm->old_image=arg.copy()/*获得独立copy*/;
    }
    else {
        _pm->old_image=arg;
    }
    _alg_or_img_change();
    update();
    imageChanged();
}

QSize PlainImageView::sizeHint() const {
    const auto & image_=this->getImage();
    if (image_.isNull()==false) {
        auto w=image_.width();
        auto h=image_.height();
        auto mwh=std::max(w,h);
        if (mwh<513) { return{w,h}; }
        auto k=512/double(mwh);
        return QSizeF{k*w,k*h}.toSize();
    }
    return{512,512};
}

void PlainImageView::_alg_or_img_change() {
    _pm->imageToDraw={};
    try {
        if (_pm->alg) {
            _pm->imageToDraw=_pm->alg->run(_pm->old_image);
        }
        else {
            _pm->imageToDraw=_pm->old_image;
        }
    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }
    _pm->isAlgUpdated=true;
    _pm->drawImage={};
}

const QImage & PlainImageView::getAlgorithmImage()const {
    if (_pm->isAlgUpdated==false) {
        const_cast<PlainImageView*>(this)->_alg_or_img_change();
    }
    return _pm->imageToDraw;
}

void PlainImageView::_p_setAlgorithm(std::shared_ptr<AbstractImageShift> var) {
    if (var==_pm->alg) { return; }
    _pm->isAlgUpdated=false;
    _pm->alg=std::move(var);
    _alg_or_img_change();
    update();
    algorithmChanged();
}

const std::shared_ptr<AbstractImageShift> & PlainImageView::getAlgorithm()const {
    return _pm->alg;
}

const QImage & PlainImageView::getImage()const {
    return _pm->old_image;
}










