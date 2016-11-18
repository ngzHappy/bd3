#include "DataChartView.hpp"

DataChartView::DataChartView(QWidget *p)
    :_Super(p){

    auto varChart = new ChartBasic;
    varChart->setParent(this);
    this->setChart(varChart);

}



















