#ifndef CHARTBASIC_HPP
#define CHARTBASIC_HPP

#include "OpenCVBasic.hpp"
#include <QtCharts/qchart.h>
namespace QtCharts {
class QValueAxis;
}

class OPENCV3_BASICHARED_EXPORT ChartBasic :public QtCharts::QChart {
    Q_OBJECT

private:
    using _Super=QtCharts::QChart;
    QtCharts::QValueAxis *_p_x=nullptr;
    QtCharts::QValueAxis *_p_y=nullptr;
public:
    ~ChartBasic();
    ChartBasic(QGraphicsItem *parent=nullptr,Qt::WindowFlags wFlags=Qt::WindowFlags());
     
    QtCharts::QValueAxis *imageXAxis()const { return _p_x; }
    QtCharts::QValueAxis *imageYAxis()const { return _p_y; }

private:
    CPLUSPLUS_OBJECT(ChartBasic)
};

#endif // CHARTBASIC_HPP
