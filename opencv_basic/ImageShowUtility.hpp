#ifndef IMAGESHOWUTILITY_HPP
#define IMAGESHOWUTILITY_HPP

namespace QtCharts {}
#include <QtCharts>
#include <algorithm>
#include <QtCore/qlist.h>
#include <QtCore/qvector.h>
#include "ChartView.hpp"
#include "ImageChart.hpp"
#include "ChartBasic.hpp"
#include "OpenCVBasic.hpp"
#include "QOpencvImage.hpp"
#include "DataChartView.hpp"
#include "PlainImageView.hpp"
#include "ImageChartView.hpp"
#include "ToolOpencvMemory.hpp"
#include "ImageShowWidget.hpp"
#include "OpencvMainWindow.hpp"
#include "ToolOpencvException.hpp"
#include "OpencvApplication.hpp"

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

template<typename __U__>
inline ChartBasic * attachAxis(ChartBasic * x,__U__ * c) {
    c->attachAxis(x->imageXAxis());
    c->attachAxis(x->imageYAxis());
    return x;
}

template<typename _Tb_,typename _Te_>
inline void fitChartAxisRange(
    ChartBasic *argC,
    const _Tb_& b,
    const _Te_ &e) {
    constexpr double m=0.05;
    using _type_t=qreal;
    if (b!=e) {
        
        {
            auto xAxis=std::minmax_element(b,e,
                [](const auto &x,const auto &y) {
                return autoGetX(x)<autoGetX(y);
            });
            const auto &xmin=*xAxis.first;
            const auto &xmax=*xAxis.second;
            auto distance=std::max(static_cast<_type_t>(0),
                static_cast<_type_t>(autoGetX(xmax))-autoGetX(xmin));
            distance*=static_cast<_type_t>(m);
            argC->imageXAxis()->setRange(
                autoGetX(xmin)-distance,autoGetX(xmax)+distance
            );
        }

        {
            auto yAxis=std::minmax_element(b,e,
                [](const auto &x,const auto &y) {
                return autoGetY(x)<autoGetY(y);
            });
            const auto &ymin=*yAxis.first;
            const auto &ymax=*yAxis.second;
            auto distance=std::max(static_cast<_type_t>(0),
                static_cast<_type_t>(autoGetY(ymax))-autoGetY(ymin));
            distance*=static_cast<_type_t>(m);
            argC->imageYAxis()->setRange(
                autoGetY(ymin)-distance,autoGetY(ymax)+distance
            );
        }

    }
}

template<
    typename _L_=QtCharts::QLineSeries,
    typename _Tb_,
    typename _Te_
>
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
    attachAxis(argC,ans);
    return ans;
}

template<
    typename _L_=QtCharts::QLineSeries,
    typename _U_
>
inline _L_ *_1c_line_like_addLineSeries(
    ChartBasic *argC,const _U_ &varPoints_
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
    ans->replace(varPoints_);

    /*将曲线加入chart,并设置坐标轴*/
    argC->addSeries(ans);
    attachAxis(argC,ans);
    return ans;
}

template<
    typename _L_=QtCharts::QLineSeries,
    typename _U_
>
inline _L_ *_1m_line_like_addLineSeries(
    ChartBasic *argC,_U_ &&varPoints
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
    ans->replace(std::move(varPoints));

    /*将曲线加入chart,并设置坐标轴*/
    argC->addSeries(ans);
    attachAxis(argC,ans);
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
    typename _Te_=std::enable_if_t<HasBeginEnd<_Tb_>::value>
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
    ChartBasic *argC,_Tb_(&argB_)[_N_]
) {
    return addLineSeries(argC,
        static_cast<const _Tb_*>(argB_),
        static_cast<const _Tb_*>(argB_)+_N_);
}

template<
    typename _U_,
    typename=std::enable_if_t< HasBeginEnd<_U_>::value >,
    typename=int *,typename=double*,typename=float*
>
inline QtCharts::QLineSeries *addLineSeries(ChartBasic *argC,_U_&&arg) {
    /*it was light weight data , not matter move or not*/
    /*c++17 rewrite it by constexpr if check has size()*/
    return _line_like_addLineSeries<QtCharts::QLineSeries>(argC,
        std::forward<_U_>(arg).begin(),
        std::forward<_U_>(arg).end());
}

inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,const QVector<QPointF> &arg) {
    return _1c_line_like_addLineSeries<QtCharts::QLineSeries>(
        argC,arg);
}

inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,const QVector<QPointF> &&arg) {
    return _1c_line_like_addLineSeries<QtCharts::QLineSeries>(
        argC,arg);
}

inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,QVector<QPointF> &arg) {
    return _1c_line_like_addLineSeries<QtCharts::QLineSeries>(
        argC,arg);
}

inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,QVector<QPointF> &&arg) {
    return _1m_line_like_addLineSeries<QtCharts::QLineSeries>(
        argC,std::move(arg));
}

inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,const QList<QPointF> &arg) {
    return _1c_line_like_addLineSeries<QtCharts::QLineSeries>(
        argC,arg);
}

inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,const QList<QPointF> &&arg) {
    return _1c_line_like_addLineSeries<QtCharts::QLineSeries>(
        argC,arg);
}

inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,QList<QPointF> &arg) {
    return _1c_line_like_addLineSeries<QtCharts::QLineSeries>(
        argC,arg);
}

inline QtCharts::QLineSeries *addLineSeries(
    ChartBasic *argC,QList<QPointF> &&arg) {
    return _1m_line_like_addLineSeries<QtCharts::QLineSeries>(
        argC,std::move(arg));
}

template<typename _Tb_,typename _Te_>
inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,const _Tb_&argB_,const _Te_&argE
) {
    return _line_like_addLineSeries<QtCharts::QScatterSeries>(argC,argB_,argE);
}

template<
    typename _Tb_,
    typename _Te_=std::enable_if_t<HasBeginEnd<_Tb_>::value>
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
    ChartBasic *argC,_Tb_(&argB_)[_N_]
) {
    return addScatterSeries(argC,
        static_cast<const _Tb_*>(argB_),
        static_cast<const _Tb_*>(argB_)+_N_);
}

template<
    typename _U_,
    typename=std::enable_if_t< HasBeginEnd<_U_>::value >,
    typename=int *,typename=double*,typename=float*
>
inline QtCharts::QScatterSeries *addScatterSeries(ChartBasic *argC,_U_&&arg) {
    /*it was light weight data , not matter move or not*/
    /*c++17 rewrite it by constexpr if check has size()*/
    return _line_like_addLineSeries<QtCharts::QScatterSeries>(argC,
        std::forward<_U_>(arg).begin(),
        std::forward<_U_>(arg).end());
}

inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,const QVector<QPointF> &arg) {
    return _1c_line_like_addLineSeries<QtCharts::QScatterSeries>(
        argC,arg);
}

inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,const QVector<QPointF> &&arg) {
    return _1c_line_like_addLineSeries<QtCharts::QScatterSeries>(
        argC,arg);
}

inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,QVector<QPointF> &arg) {
    return _1c_line_like_addLineSeries<QtCharts::QScatterSeries>(
        argC,arg);
}

inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,QVector<QPointF> &&arg) {
    return _1m_line_like_addLineSeries<QtCharts::QScatterSeries>(
        argC,std::move(arg));
}

inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,const QList<QPointF> &arg) {
    return _1c_line_like_addLineSeries<QtCharts::QScatterSeries>(
        argC,arg);
}

inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,const QList<QPointF> &&arg) {
    return _1c_line_like_addLineSeries<QtCharts::QScatterSeries>(
        argC,arg);
}

inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,QList<QPointF> &arg) {
    return _1c_line_like_addLineSeries<QtCharts::QScatterSeries>(
        argC,arg);
}

inline QtCharts::QScatterSeries *addScatterSeries(
    ChartBasic *argC,QList<QPointF> &&arg) {
    return _1m_line_like_addLineSeries<QtCharts::QScatterSeries>(
        argC,std::move(arg));
}

}/*__ImageShowUtility*/
}/*__private*/

using __private::__ImageShowUtility::addLineSeries;
using __private::__ImageShowUtility::addScatterSeries;
using __private::__ImageShowUtility::attachAxis;
using __private::__ImageShowUtility::fitChartAxisRange;

#endif // IMAGESHOWUTILITY_HPP


