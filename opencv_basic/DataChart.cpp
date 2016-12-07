#include "DataChart.hpp"
#include "AbstractImageShift.hpp"
#include <QtGui/qpainter.h>
#include <QtCharts/qvalueaxis.h>

DataChart::DataChart(QGraphicsItem *parent,Qt::WindowFlags wFlags):
    _Super(parent,wFlags) {

}

void DataChart::paint(
    QPainter *painterx,
    const QStyleOptionGraphicsItem *a,
    QWidget *b) {

    {/*绘制背景，不考虑缩放*/
        painterx->save();
        painterx->setBrush(this->backgroundBrush());
        painterx->drawRect(this->rect());
        painterx->restore();
    }

    if (_drawFunction) try {
        auto & painter=*painterx;
        painter.save();

        auto translate_=this->mapToPosition({ 0,0 });
        auto scale_=this->mapToPosition({ 1,1 })-translate_;
        painter.translate(translate_);
        painter.scale(scale_.x(),scale_.y());

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

DataChart::~DataChart() {

}

void DataChart::setDrawFunction(DrawFunctionType &&arg) {
    if (arg==_drawFunction) { return; }
    _drawFunction=std::move(arg);
    this->update();
    algorithmChanged();
}


