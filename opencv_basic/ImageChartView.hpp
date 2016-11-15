#ifndef IMAGECHARTVIEW_HPP
#define IMAGECHARTVIEW_HPP

#include "ChartView.hpp"

class ImageChartView : public ChartView
{
    Q_OBJECT

private:
    using _Super=ChartView;
public:
    ImageChartView(QWidget *parent=nullptr);
    ~ImageChartView();
};

#endif // IMAGECHARTVIEW_HPP