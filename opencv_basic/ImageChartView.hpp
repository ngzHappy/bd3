#ifndef IMAGECHARTVIEW_HPP
#define IMAGECHARTVIEW_HPP

#include "ChartView.hpp"
class ImageChart;

class ImageChartView : public ChartView
{
    Q_OBJECT

private:
    using _Super=ChartView;
    ImageChart * _mp_image_chart;
public:
    ImageChartView(QWidget *parent=nullptr);
    ~ImageChartView();
    ImageChart * imageChart()const{return _mp_image_chart;}
private:
    CPLUSPLUS_OBJECT(ImageChartView)
};

#endif // IMAGECHARTVIEW_HPP
