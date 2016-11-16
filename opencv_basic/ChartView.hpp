#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <QtCharts/qchart.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include "OpenCVBasic.hpp"

class OPENCV3_BASICHARED_EXPORT ChartView : public QtCharts::QChartView {
    Q_OBJECT

private:
    using _Super=QtCharts::QChartView;
protected:
    ChartView(QtCharts::QChart *chart,QWidget *parent=nullptr);
public:
    ChartView(QWidget *parent=nullptr):ChartView(nullptr,parent) {}
    ~ChartView();

    QSize sizeHint() const override;
private:
    CPLUSPLUS_OBJECT(ChartView)
};

#endif // CHARTVIEW_HPP
