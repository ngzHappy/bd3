#include "DataChartView.hpp"
#include "DataChart.hpp"

DataChartView::DataChartView(QtCharts::QChart *chart,QWidget *parent):
    _Super(chart,parent) {
}

DataChartView::DataChartView(QWidget *p)
    :_Super(new DataChart,p){

    auto varChart = this->dataChart();
    varChart->setParent(this);

}



















