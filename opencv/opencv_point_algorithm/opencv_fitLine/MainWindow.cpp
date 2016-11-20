/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "private/FitLineDialog.hpp"
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
    class EvalLinePoint {
        using f1type_=qreal;
        f1type_ cx0=0; f1type_ cy0=0;
        f1type_ cdx=0; f1type_ cdy=0;
        f1type_ cymin=0; f1type_ cymax=0;
    public:
        template<typename T0,typename T1,
            typename T2,typename T3,
            typename T4,typename T5
        >
            EvalLinePoint(T0&&a,T1&&b,T2&&c,T3&&d,T4&&e,T5&&f):
            cx0(a),cy0(b),cdx(c),cdy(d),cymin(e),cymax(f) {
            if (cdx==0) { return; }
            cdy/=cdx; cdx=1;
        }

        template<typename T0>
        f1type_ operator()(T0 && x)const {
            const f1type_ _dx=x-cx0;
            if (cdx==0) {
                if (_dx>0) { return cymax; }
                return cymin;
            }
            return cy0+cdy*_dx;
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
        data_points2d=toCVFloat32Point2Vector(arg_b,arg_e);
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
            constexpr auto cols=2;

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

        auto & chart=data_chart;
        auto xMax=chart->imageXAxis()->max();
        auto xMin=chart->imageXAxis()->min();
        const EvalLinePoint eval(varAns[2],varAns[3],
            varAns[0],varAns[1],
            chart->imageYAxis()->min(),
            chart->imageYAxis()->max());
        const QList<QPointF> points{
            QPointF(xMin,eval(xMin)),
            QPointF(xMax,eval(xMax)),
        };

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
    if (points2d.second<=points2d.first) {
        return;
    }

    /*设置视图*/
    auto&& mainView=makeStackPointer<SubImageShowWidget>(
        points2d.first,points2d.second);
    this->addWidget(mainView.release())
        ->resize(128+600,600);

}

/*End of the file.*/

