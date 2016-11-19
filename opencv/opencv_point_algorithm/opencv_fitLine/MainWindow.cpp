/*MainWindow.cpp*/
#include "MainWindow.hpp"
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

class EvalLinePoint {
    using f1type_=qreal;
    f1type_ cx0=0;
    f1type_ cy0=0;
    f1type_ cdx=0;
    f1type_ cdy=0;
public:
    template<typename T0,typename T1,
        typename T2,typename T3>
        EvalLinePoint(T0&&a,T1&&b,T2&&c,T3&&d):
        cx0(a),cy0(b),cdx(c),cdy(d) {
        if (cdx==0) { return; }
        cdy/=cdx; cdx=1;
    }

    template<typename T0>
    f1type_ operator()(T0 && x)const {
        if (cdx==0) { return cy0; }
        f1type_ _dx=x-cx0;
        return cy0+cdy*_dx;
    }

};

}/**/

void MainWindow::openLua() {
    using namespace memory;
    /*获得数据*/
    auto points2d=qApp()->getPoint2d();
    /*检查数据*/
    auto rows=(points2d.second-points2d.first);
    constexpr auto cols=2;
    if (rows<0) {
        return;
    }
    /*设置视图*/
    auto&& mainView=makeStackPointer<ImageShowWidget>();
    auto&& view=makeStackPointer<DataChartView>();

    mainView->setChartView(view.release());
    auto chart=view->dataChart();
    /*调整坐标轴*/
    fitChartAxisRange(chart,points2d.first,points2d.second);

    {
        auto series=
            addScatterSeries(chart,points2d.first,points2d.second);
        series->setPen(QPen(QColor(233,6,2,177),0));
        series->setBrush(QColor(233,6,2,80));
    }

    addWidget(mainView.release())->resize(600,600);

    /*opencv 曲线拟合*/
    try {
        auto input_data=
            toCVFloat32Point2Vector(points2d.first,points2d.second);
        cv::Mat data(
                    rows,
                    cols/*2*/,
                    cv::DataType<cv::Point2f::value_type>::type,
                    input_data.data()
        );

        /*dx,dy,x0,y0*/
        cv::Vec4f varAns;
        cv::fitLine(data,varAns,
                    cv::DIST_L2/*最小二乘法*/,
                    0,
                    0.01,
                    0.01);

        {
            auto xMax=chart->imageXAxis()->max();
            auto xMin=chart->imageXAxis()->min();
            const EvalLinePoint eval(varAns[2],varAns[3],
                varAns[0],varAns[1]);
            const QPointF points[2]{
                QPointF(xMin,eval(xMin)),
                QPointF(xMax,eval(xMax)),
            };
            addLineSeries(chart,points)
                ->setPen(QPen(QColor(2,215,4),1.6));
        }
    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }

}

/*End of the file.*/

