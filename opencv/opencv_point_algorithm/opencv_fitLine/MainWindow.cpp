/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "private/FitLineDialog.hpp"
#include <cmath>
#include <limits>
#include <cassert>
#include <algorithm>
#include <OpenCVUtility.hpp>

class MainWindow::_PrivateMainWindow {
public:
private:
    CPLUSPLUS_OBJECT(_PrivateMainWindow)
};

MainWindow::MainWindow(QWidget *parent):
    _Super(parent) {
    _thisp=new _PrivateMainWindow;

}

MainWindow::~MainWindow() {
    delete _thisp;
}

/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    return _Super::addImage(arg);
}

namespace {

class SubImageShowWidget :public ImageShowWidget {
    /*给出的点必须位于矩形内*/
    template<typename _t_=double>
    class LineCutXYBox {
        using _value_type=_t_;
        static_assert(false==std::is_reference<_t_>::value,"");
        typedef std::numeric_limits<_value_type> _lt_;
        static_assert(_lt_::has_infinity,"");
        static_assert(_lt_::has_quiet_NaN,"");
        constexpr static auto __nan() { return _lt_::quiet_NaN(); }
        constexpr static auto __inf() { return _lt_::infinity(); }
        constexpr static auto _negative_inf() { return -__inf(); }
        template<typename __I_>
        static bool _isNan(__I_&&arg) { return std::isnan(arg); }
        template<typename __I_>
        static bool _isInf(__I_&&arg) { return std::isfinite(arg); }
        template<typename __I_>
        static bool _isNegativeInf(__I_&&arg) {
            return std::signbit(arg)&&_isInf(arg);
        }
        template<typename __I_>
        static bool _isPositiveInf(__I_&&arg) {
            return (false==std::signbit(arg))&&_isInf(arg);
        }
        /*矩形边框*/
        _t_ _boxXMin; _t_ _boxXMax;
        _t_ _boxYMin; _t_ _boxYMax;
        /**/
        _t_ _px; _t_ _py;
        _t_ _dx; _t_ _dy;
        /*斜率*/
        /**
        p2----------p1
        | k2    k1  |
        |  p(x,y)   |
        | k3    k0  |
        p3----------p0
        **/
        _t_ _k0;// =_nan();
        _t_ _k1;// =_nan();
        _t_ _k2;// =_nan();
        _t_ _k3;// =_nan();
        _t_ _k;// =_nan();

        const _t_&_p0_x() const { return _boxXMax; }
        const _t_&_p0_y() const { return _boxYMin; }

        const _t_&_p1_x() const { return _boxXMax; }
        const _t_&_p1_y() const { return _boxYMax; }

        const _t_&_p2_x() const { return _boxXMin; }
        const _t_&_p2_y() const { return _boxYMax; }

        const _t_&_p3_x() const { return _boxXMin; }
        const _t_&_p3_y() const { return _boxYMin; }

        static _t_ &_ans_0_x(_t_ * arg) { return *arg; }
        static _t_ &_ans_0_y(_t_ * arg) { return *(1+arg); }
        static _t_ &_ans_1_x(_t_ * arg) { return *(2+arg); }
        static _t_ &_ans_1_y(_t_ * arg) { return *(3+arg); }
    public:

        template<
            typename _BoxXMin,typename _BoxXMax,
            typename _BoxYMin,typename _BoxYMax,
            typename _Px,typename _Py,
            typename _Dx,typename _Dy
        >/*将数据拷贝一遍,并转型*/
            LineCutXYBox(
                _BoxXMin && argXMin,_BoxXMax&& argXMax,
                _BoxYMin && argYMin,_BoxYMax&& argYMax,
                _Px && argPx,_Py && argPy,
                _Dx && argDx,_Dy && argDy,
                _t_*ans):

            _boxXMin(argXMin),_boxXMax(argXMax),
            _boxYMin(argYMin),_boxYMax(argYMax),
            _px(argPx),_py(argPy),
            _dx(argDx),_dy(argDy) {

            assert((_px>_boxXMin)&&"只支持点在矩形内");
            assert((_px<_boxXMax)&&"只支持点在矩形内");
            assert((_py>_boxYMin)&&"只支持点在矩形内");
            assert((_py<_boxYMax)&&"只支持点在矩形内");
            assert(((argDx!=0)||(argDy!=0))&&"dx,dy不能都是零");
            assert((argYMin<argYMax)&&"min必须小于max");
            assert((argXMin<argXMax)&&"min必须小于max");

            /*求斜率*/
            _k0=(_p0_y()-_py)/(_p0_x()-_px);
            _k1=(_p1_y()-_py)/(_p1_x()-_px);
            _k2=(_p2_y()-_py)/(_p2_x()-_px);
            _k3=(_p3_y()-_py)/(_p3_x()-_px);

            if (_dx) {
                _k=_dy/_dx;
            }

            /*求取结果*/
            _construct(ans);
        }
    private:
        void _construct(_t_ * ans) const {

            if (_dx==0) {
                _ans_0_x(ans)=_px;
                _ans_0_y(ans)=_boxYMin;
                _ans_1_x(ans)=_px;
                _ans_1_y(ans)=_boxYMax;
                return;
            }

            if (_dy==0) {
                _ans_0_x(ans)=_boxXMin;
                _ans_0_y(ans)=_py;
                _ans_1_x(ans)=_boxXMax;
                _ans_1_y(ans)=_py;
                return;
            }
            /**
            p2----------p1
            | k2  ?  k1 |
            | 0 p(x,y) 0|
            | k3  ?  k0 |
            p3----------p0
            **/

            int ansCount=0;
            if (_k==_k0) {
                _ans_0_x(ans)=_p0_x();
                _ans_0_y(ans)=_p0_y();
                ans+=2;
                ansCount=1;
            }

            if (_k==_k1) {
                _ans_0_x(ans)=_p1_x();
                _ans_0_y(ans)=_p1_y();
                ans+=2;
                ++ansCount;
            }

            if (ansCount>1) { return; }
            if (_k==_k2) {
                _ans_0_x(ans)=_p2_x();
                _ans_0_y(ans)=_p2_y();
                ans+=2;
                ++ansCount;
            }

            if (ansCount>1) { return; }
            if (_k==_k3) {
                _ans_0_x(ans)=_p3_x();
                _ans_0_y(ans)=_p3_y();
                ans+=2;
                ++ansCount;
            }

            if (ansCount>1) { return; }
            if ((_k>_k0)&&(_k<_k1)) {
                _ans_0_x(ans)=_boxXMax;
                _ans_0_y(ans)=_k*(_boxXMax-_px)+_py;
                ans+=2;
                ++ansCount;
            }

            if (ansCount>1) { return; }
            if ((_k>_k2)&&(_k<_k3)) {
                _ans_0_x(ans)=_boxXMin;
                _ans_0_y(ans)=_k*(_boxXMin-_px)+_py;
                ++ansCount;
                ans+=2;
            }

            if (ansCount>1) { return; }
            if ((_k>_k3)||(_k<_k0)) {
                _ans_0_y(ans)=_boxYMin;
                _ans_0_x(ans)=(_boxYMin-_py)/_k+_px;
                ++ansCount;
                ans+=2;
            }

            if (ansCount>1) { return; }
            if ((_k>_k1)||(_k<_k2)) {
                _ans_0_y(ans)=_boxYMax;
                _ans_0_x(ans)=(_boxYMax-_py)/_k+_px;
                assert(ansCount==1);
            }
            else {
                assert(false);
            }

        }

    };

public:
    using points2d_t=decltype(toCVFloat32Point2Vector());
    points2d_t data_points2d;
    ChartBasic * data_chart=nullptr;
    QtCharts::QLineSeries * data_line=nullptr;
public:
    template<typename _Tb,typename _Te>
    SubImageShowWidget(const _Tb & arg_b,const _Te& arg_e) {
        /*将数据点转为opencv可识别类型*/
        data_points2d=toCVFloat32Point2Vector(arg_b,arg_e);
        {
            auto sort_function=[](const auto & a,const auto & b) {
                if (a.x<b.x) { return true; }
                if (b.x<a.x) { return false; }
                return a.y<b.y;
            };

            auto unique_function=[](const auto & a,const auto & b) {
                if (a.x==b.x) {
                    return a.y==b.y;
                }
                return false;
            };

            /*删除重复点,减少计算量*/
            std::sort(data_points2d.begin(),data_points2d.end(),
                sort_function);

            data_points2d.erase(
            std::unique(data_points2d.begin(),data_points2d.end(),
                unique_function),
                data_points2d.end()
            );

            /*有效点太少*/
            if (data_points2d.size()<2) {
                return;
            }

        }
        using namespace memory;
        /*设置散点视图*/
        auto&& view=makeStackPointer<DataChartView>();
        this->setChartView(view.release());
        data_chart=view->dataChart();
        /*调整坐标轴*/
        fitChartAxisRange(data_chart,
            data_points2d.begin(),
            data_points2d.end());
        /*增加散点*/
        {
            auto series=
                addScatterSeries(data_chart,arg_b,arg_e);
            series->setPen(QPen(QColor(233,6,2,177),0));
            series->setBrush(QColor(233,6,2,80));
        }

        /*设置参数面板*/
        {
            auto && fitLineDialog=makeStackPointer<FitlineDialog>();
            this->addImageWidget(
                fitLineDialog.release(),
                Qt::RightDockWidgetArea
            )->setWindowTitle(QString::fromUtf8(
                u8R"(参数面板)"));
            /*连接信号槽*/
            connect(fitLineDialog.pointer(),
                &FitlineDialog::valueChanged,
                this,&SubImageShowWidget::updateLine);
            fitLineDialog->emitValueChanged();
        }

    }

    void updateLine(
        int distType/*算法类型*/,
        double param/*算法中的常数,如果输入0则opencv自动选择*/,
        double reps/*距离精度*/,
        double aeps/*角度精度*/) {
        /*opencv 曲线拟合*/
        try {

            auto rows=static_cast<int>(data_points2d.size());
            constexpr static auto cols=2;

            /*创建ref矩阵,不拷贝数据*/
            cv::Mat data(
                rows,
                cols/*2*/,
                cv::DataType<cv::Point2f::value_type>::type,
                data_points2d.data()
            );

            /*dx,dy,x0,y0*/
            cv::Vec4f varAns;

            /*opencv直线拟合*/
            cv::fitLine(data,varAns,
                distType,
                param,
                reps,
                aeps);

            /*绘制直线*/
            this->drawLine(varAns);

        }
        catch (...) {
            CPLUSPLUS_EXCEPTION(false);
        }
    }

    void drawLine(const cv::Vec4f & varAns) {

        if ((varAns[0]==0)&&(varAns[1]==0)) {
            return;
        }

        auto & chart=data_chart;
        QVector<QPointF> points;
        points.resize(2);

        {
            const LineCutXYBox<qreal>eval(
                chart->imageXAxis()->min(),
                chart->imageXAxis()->max(),
                chart->imageYAxis()->min(),
                chart->imageYAxis()->max(),
                varAns[2],varAns[3],
                varAns[0],varAns[1],
                reinterpret_cast<qreal*>(points.data())
            );
        }

        auto & line=data_line;
        if (line) {
            line->replace(points);
        }
        else {
            line=addLineSeries(chart,points);
            line->setPen(QPen(QColor(2,215,4),1.6));
        }

    }

private:
    CPLUSPLUS_OBJECT(SubImageShowWidget)
};

}

void MainWindow::openLua() {
    using namespace memory;
    /*获得数据*/
    auto points2d=qApp->getPoint2d();
    /*至少两个点*/
    if ((points2d.second-points2d.first)<2) {
        return;
    }

    /*设置视图*/
    auto&& mainView=makeStackPointer<SubImageShowWidget>(
        points2d.first,points2d.second);
    this->addWidget(mainView.release())
        ->resize(800,600);

}

/*End of the file.*/

