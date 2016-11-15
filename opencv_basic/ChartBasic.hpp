#ifndef CHARTBASIC_HPP
#define CHARTBASIC_HPP

#include "OpenCVBasic.hpp"
#include <QtCharts/qchart.h>

class OPENCV3_BASICHARED_EXPORT ChartBasic :public QtCharts::QChart {
    Q_OBJECT

private:
    using _Super=QtCharts::QChart;
public:
    ~ChartBasic();
    ChartBasic(QGraphicsItem *parent=nullptr,Qt::WindowFlags wFlags=Qt::WindowFlags());

private:
    CPLUSPLUS_OBJECT(ChartBasic)
};

#endif // CHARTBASIC_HPP
