#include "DataChartView.hpp"

DataChartView::DataChartView(QtCharts::QChart *chart,QWidget *parent):
    _Super(chart,parent) {
}

DataChartView::DataChartView(QWidget *p)
    :_Super(new ChartBasic,p){

    auto varChart = this->dataChart();
    varChart->setParent(this);
  
}



















