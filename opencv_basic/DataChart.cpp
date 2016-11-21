#include "DataChart.hpp"

DataChart::DataChart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    _Super(parent,wFlags){

}

void DataChart::paint(
    QPainter *painterx,
    const QStyleOptionGraphicsItem *a,QWidget *b) {
    return _Super::paint(painterx,a,b);
}

DataChart::~DataChart(){

}




