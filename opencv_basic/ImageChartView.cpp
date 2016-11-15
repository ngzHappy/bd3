#include "ImageChartView.hpp"
#include "ImageChart.hpp"

ImageChartView::ImageChartView(QWidget *parent):_Super(parent){
    _mp_image_chart=new ImageChart;
    setChart(_mp_image_chart);
}

ImageChartView::~ImageChartView() {
}




