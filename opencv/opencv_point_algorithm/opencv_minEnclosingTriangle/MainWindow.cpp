/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>

class MainWindow::_PrivateMainWindow{
public:
private:
    CPLUSPLUS_OBJECT(_PrivateMainWindow)
};

MainWindow::MainWindow(QWidget *parent) :
    _Super(parent){
    _thisp=new _PrivateMainWindow;
}

MainWindow::~MainWindow(){
    delete _thisp;
}

/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    return _Super::addImage(arg);
}

void MainWindow::openLua(){

    auto varInputData=qApp->getPoint2d();
    auto rows=varInputData.second-varInputData.first;

    if (rows<2) { return; }

    using namespace memory;
    auto && mainWidget=makeStackPointer<ImageShowWidget>();

    addWidget(mainWidget.release())
        ->resize(512,512);

    auto && chartView=makeStackPointer<DataChartView>();
    mainWidget->setChartView(chartView.release());

    auto dataChart=chartView->dataChart();

    {
        auto series=addScatterSeries(dataChart,
            varInputData.first,
            varInputData.second);
        series->setMarkerSize(6.6);
        series->setPen(QPen(QColor(222,2,2,100),1.2));
        series->setBrush(QColor(222,22,22,50));
    }

    try {

        auto cvPoionts2d=toCVFloat32Point2Vector(
            varInputData.first,
            varInputData.second);

        cv::Mat inputMat(
            cvPoionts2d.size()/*std::vector<cv::cv::Point2f>*/,
            2,
            cv::DataType<cv::Point2f::value_type>::type,
            cvPoionts2d.data()
        );

        cv::Point2f center;
        float r;
        cv::minEnclosingCircle(inputMat,center,r);

        chartView->setDrawFunction(
            [center=QPointF(center.x,center.y),r](
            QPainter*painter,const QSizeF&
        )->void {
            CosmeticQPen pen(QColor(0,0,0),2.2);
            painter->setPen(pen);
            painter->drawEllipse(center,r,r);
        });

        r*=1.05f;

        dataChart->imageXAxis()->setRange(center.x-r,center.x+r);
        dataChart->imageYAxis()->setRange(center.y-r,center.y+r);

    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }

}

/*End of the file.*/

