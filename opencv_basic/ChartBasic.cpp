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
    auto x=new __private::ValueAxis;
    auto y=new __private::ValueAxis;
    y->setReverse(true);
    this->addAxis(x,Qt::AlignBottom);
    this->addAxis(y,Qt::AlignLeft);
    this->setAnimationOptions(QChart::SeriesAnimations);
}










