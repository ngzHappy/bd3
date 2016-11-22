#include "DataChartView.hpp"
#include "DataChart.hpp"

DataChartView::DataChartView(QtCharts::QChart *chart,QWidget *parent):
    _Super(chart,parent) {
}

DataChartView::DataChartView(QWidget *p)
    :_Super(new DataChart,p){

    auto varChart = this->dataChart();
    varChart->setParent(this);

    connect(varChart,&DataChart::algorithmChanged,
        this,&DataChartView::algorithmChanged);

}

void DataChartView::_p_setAlg(DataChart::DrawFunctionType &&arg) {
    this->dataChart()->setDrawFunction(std::move(arg));
}

void DataChartView::_p_setAlg(const DataChart::DrawFunctionType &arg) {
    this->_p_setAlg(DataChart::DrawFunctionType{arg});
}

















