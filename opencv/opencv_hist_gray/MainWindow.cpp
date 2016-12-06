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
    if (arg.isNull()) { return nullptr; }
    auto varImage=arg.convertToFormat(QImage::Format_Grayscale8);
    cv::Mat varImageWrap(varImage.height(),
                         varImage.width(),
                         CV_8UC1,const_cast<uchar*>(varImage.constBits()),
                         varImage.bytesPerLine());

    auto calcGrayHist=[](cv::Mat arg)->auto {
        //opencv-master\modules\imgproc\src\histogram.cpp
        constexpr int channels[]={ 0 };
        constexpr int dims=1;
        constexpr int histSize[]={ 256 };
        constexpr float range[]={ 0.f,255.f };
        const float *ranges[]={ range };
        constexpr bool uniform=true;
        constexpr bool accumulate=false;

        std::vector<float,memory::Allocator<float>> varAns;
        try {

            varAns.resize(histSize[0],0.f);
            cv::MatND varAnsWrap(histSize[0],1,CV_32FC1,varAns.data());

            cv::calcHist(&arg,1,
                (const int*)channels,
                { /*mask*/ },
                varAnsWrap,
                dims,
                (const int*)histSize,
                (const float**)ranges,
                uniform,accumulate);

        }
        catch (...) {
            CPLUSPLUS_EXCEPTION(false);
            varAns.clear();
        }
        return std::move(varAns);
    };

    auto && histData=calcGrayHist(varImageWrap);

    using namespace memory;
    auto && view=makeStackPointer<ImageShowWidget>();
    this->addWidget(view.release());
    view->setImage(varImage);

    auto && dataView=makeStackPointer<DataChartView>();
    auto dataChart=dataView->dataChart();
    view->addImageWidget(dataView.release());

    auto && barSeries=makeStackPointer< QtCharts::QBarSeries >();
    barSeries.release()->setParent(dataChart);

    auto && barSet=makeStackPointer< QtCharts::QBarSet >("...");
    for (const auto &varI:histData) {
        barSet->append(varI);
    }

    barSet.release()->setParent(barSeries);
    barSeries->append(barSet);
    dataChart->addSeries(barSeries);

    dataChart->imageXAxis()->setRange(-.5,255.5);
    dataChart->imageYAxis()->setRange(-.5,
        *std::max_element(histData.cbegin(),histData.cend())+5.5);
    barSeries->attachAxis(dataChart->imageXAxis());
    barSeries->attachAxis(dataChart->imageYAxis());

    QColor varColor(100+(std::rand()&127),
        120+(std::rand()&127),
        100+(std::rand()&127),
        200);
    barSet->setPen(CosmeticQPen(varColor,1));
    barSet->setBrush(varColor);
    barSeries->setBarWidth(1);

    return nullptr;
}

void MainWindow::openLua() {
    return _Super::openLua();
}

/*End of the file.*/

