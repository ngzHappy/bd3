#ifndef IMAGECHART_HPP
#define IMAGECHART_HPP

#include "ChartBasic.hpp"

class ImageChart : public ChartBasic
{
    Q_OBJECT

private:
    using _Super=ChartBasic;
public:
    ImageChart(QGraphicsItem *parent=nullptr,Qt::WindowFlags wFlags=Qt::WindowFlags());
    ~ImageChart();
public:
    ImageChart(ImageChart&&);
    ImageChart(const ImageChart&);
    ImageChart&operator=(ImageChart&&)=delete;
    ImageChart&operator=(const ImageChart&)=delete;
private:
    CPLUSPLUS_OBJECT(ImageChart)
};

#endif // IMAGECHART_HPP




