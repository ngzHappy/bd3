/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>
#include "ApproxPolyDPDialog.hpp"
#include <containers/containers.hpp>
using containers::vector;

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

class DataWidget :public ImageShowWidget {
    vector<cv::Point2f> $m$Points;
    DataChartView * $m$DataChartView;
    bool $m$IsClosed;
public:
    DataWidget(vector<cv::Point2f> && arg)
        :$m$Points(std::move(arg)) {
        using namespace memory;
        if ($m$Points.empty()) { return; }
        /*判断曲线是否闭合*/
        $m$IsClosed=((*$m$Points.begin())==(*$m$Points.rbegin()));
        auto && view=makeStackPointer<DataChartView>();
        this->setChartView(view.release());
        $m$DataChartView=view;
        /*添加控制面板*/
        auto && dialog=makeStackPointer<ApproxPolyDPDialog>();
        this->addImageWidget(dialog.release(),Qt::DockWidgetArea::RightDockWidgetArea);
        connect(dialog.pointer(),&ApproxPolyDPDialog::valueChanged,
            this,&DataWidget::valueChanged);
        auto varDataChart=view->dataChart();
        {/*添加离散点图*/
            auto varSeries=addScatterSeries(varDataChart,$m$Points.cbegin(),
                $m$Points.cend());
            fitChartAxisRange(varDataChart,$m$Points.cbegin(),
                $m$Points.cend());
            varDataChart->axisY()->setReverse(true);
            QRadialGradient varRadialGradient({ .5,.5 },.5);
            varRadialGradient.setCoordinateMode(
                QRadialGradient::ObjectBoundingMode);
            varRadialGradient.setColorAt(0,QColor(3,255,3,200));
            varRadialGradient.setColorAt(0.15,QColor(1,202,3,125));
            varRadialGradient.setColorAt(0.8,QColor(1,122,3,15));
            varRadialGradient.setColorAt(1,QColor(1,122,3,3));
            varSeries->setPen(Qt::NoPen);
            varSeries->setBrush(varRadialGradient);
        }
        {/*添加直线图*/
            auto varSeries=addLineSeries(varDataChart,$m$Points.cbegin(),
                $m$Points.cend());
            fitChartAxisRange(varDataChart,$m$Points.cbegin(),
                $m$Points.cend());
            if (false==$m$IsClosed) {
                auto & varFirst=*$m$Points.begin();
                varSeries->append(varFirst.x,varFirst.y);
            }
            varSeries->setPen(CosmeticQPen(QColor(3,200,1),1.2));
        }
        dialog->emitValueChanged();
    }

    void valueChanged(double epsilon) {

        $m$DataChartView->setDrawFunction(
            [=](QPainter* argPainter,auto&) {
            try {
                /*获得数据包装*/
                cv::Mat varInput($m$Points.size(),1,CV_32FC2,
                    $m$Points.data());
                /*输出数据*/
                cv::Mat varOutput;
                /*拟合*/
                cv::approxPolyDP(varInput,varOutput,epsilon,$m$IsClosed);

                auto varDataBegin=
                    reinterpret_cast<cv::Point2f *>(varOutput.data);
                auto varDataEnd=varDataBegin+varOutput.rows;

                /*绘制*/
                QPainterPath varPainterPath;
                varPainterPath.moveTo(varDataBegin->x,varDataBegin->y);

                for (auto varI=varDataBegin; varI!=varDataEnd; ++varI) {
                    varPainterPath.lineTo(varI->x,varI->y);
                }

                if (false==$m$IsClosed) {
                    varPainterPath.lineTo(varDataBegin->x,varDataBegin->y);
                }

                argPainter->setPen(CosmeticQPen(QColor(232,52,102,222),3.2));
                argPainter->setBrush(Qt::NoBrush);
                argPainter->drawPath(varPainterPath);

            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }
        });

    }

private:
    CPLUSPLUS_OBJECT(DataWidget)
};

}/*namespace*/

void MainWindow::openLua() {
    auto varPoints=qApp->getPoint2d();
    auto varRows=varPoints.second-varPoints.first;
    if (varRows<2) { return; }

    vector<cv::Point2f> varData;
    varData.reserve(varRows);
    for (auto varI=varPoints.first; varI!=varPoints.second; ++varI) {
        varData.emplace_back(static_cast<float>(varI->x()),
            static_cast<float>(varI->y()));
    }

    using namespace memory;
    auto && view=makeStackPointer<DataWidget>(
        std::move(varData));
    this->addWidget(view.release())
        ->resize(800,600);
}

/*End of the file.*/


