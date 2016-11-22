#include "DataChart.hpp"
#include "AbstractImageShift.hpp"
#include <QtGui/qpainter.h>
#include <QtCharts/qvalueaxis.h>

DataChart::DataChart(QGraphicsItem *parent,Qt::WindowFlags wFlags):
    _Super(parent,wFlags) {

}

void DataChart::paint(
    QPainter *painterx,
    const QStyleOptionGraphicsItem *a,QWidget *b) {
    if (_drawFunction) try {
        auto & painter=*painterx;
        painter.save();

        QTransform xxx;
       
        xxx.translate( plotArea().topLeft().x(),
            plotArea().topLeft().y()
        ); 
        xxx.scale(20,20);
        
        painter.setTransform(xxx);
        

        //QRectF viewPort={
        //this->imageXAxis()->min(),
        //this->imageYAxis()->min(),
        //this->imageXAxis()->max()-this->imageXAxis()->min(),
        //this->imageYAxis()->max()-this->imageYAxis()->min(),
        //};
        //painter.setViewport(viewPort.toRect());
        //painter.setWindow(plotArea().toRect());

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


