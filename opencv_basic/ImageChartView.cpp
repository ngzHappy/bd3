#include "ImageChartView.hpp"
#include "ImageChart.hpp"

ImageChartView::ImageChartView(QWidget *parent):_Super(parent){
    _mp_image_chart=new ImageChart;
    setChart(_mp_image_chart);
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

void ImageChartView::_p_setAlgorithm(const std::shared_ptr<AbstractImageShift>&arg) {
    _mp_image_chart->setAlgorithm(arg);
}

void ImageChartView::_p_setAlgorithm(std::shared_ptr<AbstractImageShift>&&arg) {
    _mp_image_chart->setAlgorithm(std::move(arg));    
}

