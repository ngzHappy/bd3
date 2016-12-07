#include "ChartView.hpp"
#include "ChartBasic.hpp"

ChartView::ChartView(
    QtCharts::QChart *chart,
    QWidget *parent):_Super(chart,parent) {
    /*设置大小*/
    this->setMinimumSize(64,64);
    /*设置渲染算法*/
    this->setRenderHints(
        QPainter::HighQualityAntialiasing|
        QPainter::SmoothPixmapTransform|
        QPainter::TextAntialiasing|
        QPainter::Antialiasing
    );
    
}

ChartView::~ChartView() {
}

QSize ChartView::sizeHint() const {
    return{128,64};
}


















