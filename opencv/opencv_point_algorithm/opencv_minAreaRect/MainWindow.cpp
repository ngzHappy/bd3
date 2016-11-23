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

void MainWindow::openLua() {

    auto points2d=qApp->getPoint2d();
    auto cvPoionts2d=toCVFloat32Point2Vector(points2d.first,points2d.second);
    using namespace memory;

    auto && mainWidget=
        makeStackPointer<ImageShowWidget>();
    this->addWidget(mainWidget.release())
        ->resize(512,512);

    auto &&chartView=
        makeStackPointer<DataChartView>();
    mainWidget->setChartView(chartView.release());

    auto series=addScatterSeries(chartView->dataChart(),
        points2d.first,
        points2d.second);

    series->setPen(QPen(QColor(0,0,0,0),0));
    series->setBrush(QColor(210,26,36));
    series->setMarkerSize(6);

    try {

        cv::Mat inputMat(
            cvPoionts2d.size()/*std::vector<cv::cv::Point2f>*/,
            2,
            cv::DataType<cv::Point2f::value_type>::type,
            cvPoionts2d.data()
        );

        cv::Point2f ans[5];
        cv::minAreaRect(inputMat)
            .points(ans);

        ans[4]=ans[0];

        {
            cv::Point2f *ansp=ans;
            QPen pen(QColor(100,200,100),2);

            addLineSeries(chartView->dataChart(),
                ansp,ansp+2)->setPen(pen);
            addLineSeries(chartView->dataChart(),
                ansp+1,ansp+3)->setPen(pen);
            addLineSeries(chartView->dataChart(),
                ansp+2,ansp+4)->setPen(pen);
            addLineSeries(chartView->dataChart(),
                ansp+3,ansp+5)->setPen(pen);

            fitChartAxisRange(chartView->dataChart(),ansp,ansp+4);
        }

    }
    catch (...) {
        CPLUSPLUS_EXCEPTION(false);
    }

}

/*End of the file.*/

