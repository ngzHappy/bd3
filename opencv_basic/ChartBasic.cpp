#include "ChartBasic.hpp"
#include <QtCharts/qvalueaxis.h>

namespace {
namespace __private {

class ValueAxis :public QtCharts::QValueAxis {
public:
    ValueAxis() {
        setRange(0,512);
        setTickCount(5);
    }
private:
    CPLUSPLUS_OBJECT(ValueAxis)
};

}/*__private*/
}/**/


ChartBasic::~ChartBasic() {
}

ChartBasic::ChartBasic(
        QGraphicsItem *parent,
        Qt::WindowFlags wFlags):_Super(parent,wFlags) {
    _p_x=new __private::ValueAxis;
    _p_x->setParent(this);
    _p_y=new __private::ValueAxis;
    _p_y->setParent(this);
    //_p_y->setReverse(true);
    this->addAxis(_p_x,Qt::AlignBottom);
    this->addAxis(_p_y,Qt::AlignLeft);
    this->setAnimationOptions(QChart::SeriesAnimations);
    auto varLegend=legend();
    varLegend->setVisible(false);
    setPlotAreaBackgroundVisible(false);
    setBackgroundVisible(false);
}










