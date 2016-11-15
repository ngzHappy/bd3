#include "ChartView.hpp"
#include "ChartBasic.hpp"

ChartView::ChartView(
    QtCharts::QChart *chart,
    QWidget *parent):_Super(chart,parent) {
    /*设置chart*/
    this->setChart(new ChartBasic);
    /*设置大小*/
    this->setMinimumSize(64,64);
    /*设置渲染算法*/
    this->setRenderHints(
        QPainter::HighQualityAntialiasing|
        QPainter::SmoothPixmapTransform|
        QPainter::TextAntialiasing
    );
}

ChartView::~ChartView() {
}















