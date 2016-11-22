#ifndef DATACHARTVIEW_HPP
#define DATACHARTVIEW_HPP

#include "ChartView.hpp"
#include "DataChart.hpp"
#include "AbstractImageShift.hpp"

class OPENCV3_BASICHARED_EXPORT DataChartView : public ChartView {
    Q_OBJECT

private:
    using _Super=ChartView;
    DataChartView(QtCharts::QChart *chart,QWidget *parent=nullptr);
public:
    DataChartView(QWidget * parent=nullptr);

    DataChart * dataChart()const {
        return static_cast<DataChart *>(chart());
    }

public:

    template<typename _DrawFunction_,
        typename=decltype((std::declval<_DrawFunction_&&>())
        (std::declval<QPainter*>(),std::declval<const QSizeF&>()))>
        inline void setDrawFunction(_DrawFunction_&&);

    template<typename _DrawFunction_,
        typename=void*,
        typename=decltype((std::declval<_DrawFunction_&&>())
            ->paint(std::declval<QPainter*>(),std::declval<const QSizeF&>())) >
        inline void setDrawFunction(_DrawFunction_&&);

public:
    Q_SIGNAL void algorithmChanged();
private:
    void _p_setAlg(DataChart::DrawFunctionType &&);
    void _p_setAlg(const DataChart::DrawFunctionType &);
private:
    CPLUSPLUS_OBJECT(DataChartView)
};

template<typename _DrawFunction_,typename>
void DataChartView::setDrawFunction(_DrawFunction_&&arg) {
    class _AF_ final :public AbstractDrawFunction {
        using _DT_=std::remove_reference_t<_DrawFunction_>;
        _DT_ _call_back_function_;
    public:
        _AF_(_DrawFunction_&&arg):_call_back_function_(
        std::forward<_DrawFunction_>(arg)) {}

        void paint(QPainter *p,
            const QSizeF &s)override {
            _call_back_function_(p,s);
        }

    };
    this->_p_setAlg(memory::make_shared<_AF_>(
        std::forward<_DrawFunction_>(arg)));
}

template<typename _DrawFunction_,typename,typename>
inline void setDrawFunction(_DrawFunction_&&arg) {
    _p_setAlg(std::forward<_DrawFunction_>(arg));
}

#endif // DATACHARTVIEW_HPP
