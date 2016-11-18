#include "ImageChartView.hpp"
#include "ImageChart.hpp"
#include <algorithm>

ImageChartView::ImageChartView(
    QtCharts::QChart *chart,QWidget *parent)
    :_Super(chart,parent) {
}

ImageChartView::ImageChartView(QWidget *parent)
    :ImageChartView(new ImageChart,parent) {
    _mp_image_chart=static_cast<ImageChart*>(chart());
    _mp_image_chart->setParent(this);

    connect(_mp_image_chart,&ImageChart::imageChanged,
        this,&ImageChartView::imageChanged);
    connect(_mp_image_chart,&ImageChart::algorithmChanged,
        this,&ImageChartView::algorithmChanged);
}

ImageChartView::~ImageChartView() {
}

ImageChart * ImageChartView::setImage(const QImage &arg,bool _copy) {
    _mp_image_chart->setImage(arg,_copy);
    return _mp_image_chart;
}

const QImage &ImageChartView::getImage()const {
    return _mp_image_chart->getImage();
}

const QImage &ImageChartView::getAlgorithmImage()const {
    return _mp_image_chart->getAlgorithmImage();
}

const std::shared_ptr<AbstractImageShift>&
ImageChartView::getAlgorithm()const {
    return _mp_image_chart->getAlgorithm();
}

QSize ImageChartView::sizeHint() const {
    const auto & image_=_mp_image_chart->getImage();
    if (image_.isNull()==false) {
        auto w=image_.width();
        auto h=image_.height();
        auto mwh=std::max(w,h);
        if (mwh<513) { return{ w,h }; }
        auto k=512/double(mwh);
        return QSizeF{ k*w,k*h }.toSize();
    }
    return{ 512,512 };
}

void ImageChartView::_p_setAlgorithm(const std::shared_ptr<AbstractImageShift>&arg) {
    _mp_image_chart->setAlgorithm(arg);
}

void ImageChartView::_p_setAlgorithm(std::shared_ptr<AbstractImageShift>&&arg) {
    _mp_image_chart->setAlgorithm(std::move(arg));
}

