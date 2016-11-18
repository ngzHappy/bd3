#ifndef DATACHARTVIEW_HPP
#define DATACHARTVIEW_HPP

#include "ChartView.hpp"
#include "ChartBasic.hpp"

class OPENCV3_BASICHARED_EXPORT DataChartView : public ChartView
{
    Q_OBJECT

private:
    using _Super=ChartView;
    DataChartView(QtCharts::QChart *chart,QWidget *parent=nullptr);
public:
    DataChartView(QWidget * parent=nullptr);

    ChartBasic * dataChart()const{
        return static_cast<ChartBasic *>(chart());}

private:
    CPLUSPLUS_OBJECT(DataChartView)
};

#endif // DATACHARTVIEW_HPP
