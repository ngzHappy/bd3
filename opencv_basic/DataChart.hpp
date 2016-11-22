﻿#ifndef DATACHART_HPP
#define DATACHART_HPP

#include "ChartBasic.hpp"
class AbstractDrawFunction;

class OPENCV3_BASICHARED_EXPORT DataChart : public ChartBasic {
    Q_OBJECT

private:
    using _Super=ChartBasic;
public:
    using DrawFunctionType=std::shared_ptr<AbstractDrawFunction>;
    DrawFunctionType _drawFunction;
public:
    DataChart(QGraphicsItem *parent=nullptr,Qt::WindowFlags wFlags=Qt::WindowFlags());
    ~DataChart();

    const  DrawFunctionType & getDrawFunction() const { return _drawFunction; }
    void setDrawFunction(DrawFunctionType &&);
    void setDrawFunction(const DrawFunctionType &arg) {
        setDrawFunction(DrawFunctionType{ arg });
    }

public:
    Q_SIGNAL void algorithmChanged();
protected:
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *,QWidget *)override;
private:
    CPLUSPLUS_OBJECT(DataChart)
};

#endif // DATACHART_HPP
