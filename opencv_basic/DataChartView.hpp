#ifndef DATACHARTVIEW_HPP
#define DATACHARTVIEW_HPP

#include "ChartView.hpp"
#include "ChartBasic.hpp"

class DataChartView : public ChartView
{
    Q_OBJECT

private:
    using _Super=ChartView;
public:
    DataChartView(QWidget * parent=nullptr);

    ChartBasic * dataChart()const{
        static_cast<ChartBasic *>(chart());}

private:
    CPLUSPLUS_OBJECT(DataChartView)
};

#endif // DATACHARTVIEW_HPP
