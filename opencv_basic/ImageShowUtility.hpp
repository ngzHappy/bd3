#ifndef IMAGESHOWUTILITY_HPP
#define IMAGESHOWUTILITY_HPP

namespace QtCharts {}
#include <QtCharts>
#include <QtCore/qlist.h>
#include <QtCore/qvector.h>
#include "ChartView.hpp"
#include "ImageChart.hpp"
#include "ChartBasic.hpp"
#include "OpenCVBasic.hpp"
#include "QOpencvImage.hpp"
#include "PlainImageView.hpp"
#include "ImageChartView.hpp"
#include "ToolOpencvMemory.hpp"
#include "ImageShowWidget.hpp"
#include "OpencvMainWindow.hpp"
#include "ToolOpencvException.hpp"

namespace __private {
namespace __ImageShowUtility {

template<typename ...>using _void_t=void;

template<typename _T_,typename=void,typename=void>
class HasBeginEnd :public std::false_type {
};

template<typename _T_>
class HasBeginEnd<_T_,
    _void_t<decltype((std::declval<_T_>()).begin())>,
    _void_t<decltype((std::declval<_T_>()).end())>
> :public std::true_type {
};

template<typename _T_,typename=void,typename=void>
class HasStarBeginEnd :public std::false_type {
};

template<typename _T_>
class HasStarBeginEnd<_T_,
    _void_t<decltype((*std::declval<_T_>()).begin())>,
    _void_t<decltype((*std::declval<_T_>()).end())>
> :public std::true_type {
};

template<typename _Tb_,typename _Te_,typename=void>
class Distance {
public:
    static int value(const _Tb_ & argB,const _Te_&argE) {
        int ans=0;
        auto argB_=argB;
        for (; argB_!=argE; ++argB_) { ++ans; }
        return ans;
    }
};

template<typename _Tb_,typename _Te_>
class Distance<_Tb_,_Te_,
    _void_t<decltype((std::declval<const _Te_ &>())-(std::declval<const _Tb_&>()))>>{
public:
    static int value(const _Tb_&argB,const _Te_&argE) {
        return static_cast<int>(argE-argB);
    }
};

template<
    typename _XTT_,
    typename _U___=void
>
class HasXFunction :public std::false_type {
public:
};


template<
    typename _XTT_
>
class HasXFunction<_XTT_,
    _void_t< decltype(((std::declval<_XTT_>()).x())) >
> :public std::true_type {
};

template<
    typename _xT_,
    typename _2U_=std::enable_if_t< HasXFunction<const _xT_&>::value >
>
auto autoGetX(const _xT_&arg) {
    return arg.x();
}

template<typename _xT_,
    typename _U_=std::enable_if_t<!HasXFunction<const _xT_&>::value>,
    typename _U1_=void*>
    const auto & autoGetX(const _xT_&arg) {
    return arg.x;
}

template<
    typename _xT_,
    typename _2U_=std::enable_if_t< HasXFunction<const _xT_&>::value >
>
auto autoGetY(const _xT_&arg) {
    return arg.y();
}

template<typename _xT_,
    typename _U_=std::enable_if_t<!HasXFunction<const _xT_&>::value>,
    typename _U1_=void*>
    const auto & autoGetY(const _xT_&arg) {
    return arg.y;
}

template<typename _L_=QtCharts::QLineSeries,typename _Tb_,typename _Te_>
inline _L_ *_line_like_addLineSeries(
    ChartBasic *argC,const _Tb_&argB_,const _Te_&argE
) {
    class LineSeries :public _L_ {
        using _Super=_L_;
    public:
        using _Super::_Super;
        using _Super::replace;
        using _Super::attachAxis;
    private:
        CPLUSPLUS_OBJECT(LineSeries)
    };
    auto ans=new LineSeries;

    QVector<QPointF> varPoints;
    auto argB=argB_/*copy create it*/;
    varPoints.reserve(Distance<const _Tb_&,const _Te_&>::value(argB_,argE));
    for (; argB!=argE; ++argB) {
        const auto & _var=*argB;
        varPoints.push_back(QPointF(autoGetX(_var),autoGetY(_var)));
    }
    ans->replace(std::move(varPoints));

    /*将曲线加入chart,并设置坐标轴*/
    argC->addSeries(ans);
    ans->attachAxis(argC->imageXAxis());
    ans->attachAxis(argC->imageYAxis());

    return ans;
}

template<typename _Tb_,typename _Te_>
inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,const _Tb_&argB_,const _Te_&argE
) {
    return _line_like_addLineSeries<QtCharts::QLineSeries>(argC,argB_,argE);
}

template<
    typename _Tb_,
    typename _Te_= std::enable_if_t<HasBeginEnd<_Tb_>::value>
>
inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,const _Tb_&argB_
) {
    return addLineSeries(argC,argB_.begin(),argB_.end());
}

template<
    typename _Tb_,
    int _N_
>
inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,_Tb_(&argB_) [_N_]
) {
    return addLineSeries(argC,
        static_cast<const _Tb_*>(argB_),
        static_cast<const _Tb_*>(argB_)+_N_);
}

template<typename _Tb_,typename _Te_>
inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,const _Tb_&argB_,const _Te_&argE
) {
    return _line_like_addLineSeries<QtCharts::QScatterSeries>(argC,argB_,argE);
}

template<
    typename _Tb_,
    typename _Te_= std::enable_if_t<HasBeginEnd<_Tb_>::value>
>
inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,const _Tb_&argB_
) {
    return addScatterSeries(argC,argB_.begin(),argB_.end());
}

template<
    typename _Tb_,
    int _N_
>
inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,_Tb_(&argB_) [_N_]
) {
    return addScatterSeries(argC,
        static_cast<const _Tb_*>(argB_),
        static_cast<const _Tb_*>(argB_)+_N_);
}

}/*__ImageShowUtility*/
}/*__private*/

using __private::__ImageShowUtility::addLineSeries;
using __private::__ImageShowUtility::addScatterSeries;

#endif // IMAGESHOWUTILITY_HPP


