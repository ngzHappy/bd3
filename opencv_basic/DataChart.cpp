#include "DataChart.hpp"
#include "AbstractImageShift.hpp"
#include <QtGui/qpainter.h>

DataChart::DataChart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    _Super(parent,wFlags){

}

void DataChart::paint(
    QPainter *painterx,
    const QStyleOptionGraphicsItem *a,QWidget *b) {
    if (_drawFunction) try {
        auto & painter=*painterx;
        painter.save();
        painter.translate(plotArea().topLeft());
        try {
            _drawFunction->paint(&painter,
                plotArea().size());
        }
        catch (...) {
            painter.restore();
            throw;
        }
        painter.restore();
    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }
    return _Super::paint(painterx,a,b);
}

DataChart::~DataChart(){

}

void DataChart::setDrawFunction(DrawFunctionType &&arg) {
    if (arg==_drawFunction) { return; }
    _drawFunction=std::move(arg);
    this->update();
    algorithmChanged();
}


