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
QWidget* MainWindow::addImage(const QImage &arg) try {
    if (arg.isNull()) { return nullptr; }
    /*转化为灰度图*/
    auto varGrayImage=
        arg.convertToFormat(QImage::Format_Grayscale8);
    /*用opencv包装数据*/
    cv::Mat varInput(varGrayImage.height(),
        varGrayImage.width(),
        CV_8UC1,
        const_cast<uchar *>(varGrayImage.constBits()),
        varGrayImage.bytesPerLine());
    /*二值化*/
    cv::threshold(varInput,varInput,125.5,255,cv::THRESH_BINARY);
    /*查找边界*/
    std::vector<std::vector<cv::Point>> varContours;
    cv::findContours(varInput,varContours,
        cv::RETR_EXTERNAL,
        cv::CHAIN_APPROX_SIMPLE);
    if (varContours.empty()) { return nullptr; }
    /*找到最大边界*/
    std::sort(varContours.begin(),varContours.end(),
        [](auto &l,auto &r) {return l.size()>r.size(); });
    varContours.resize(1);
    auto & varContour=varContours[0];
    if (varContour.empty()) { return nullptr; }
    /*寻找凸包*/
    std::vector<std::int32_t> varConvexHullIndex;
    cv::convexHull(varContour,varConvexHullIndex);
    /*寻找凸包缺陷*/
    /*（startPoint）(endPoint)(farPoint)(depth)*/
    std::vector<cv::Vec4i> varAns;
    cv::convexityDefects(
        varContour,
        varConvexHullIndex,
        varAns
    );
    /*绘制图形*/
    using namespace memory;
    auto && varImageShowWidget=makeStackPointer<ImageShowWidget>();

    auto varChartImage=varImageShowWidget->setChartImage(varGrayImage);

    {
        QPointF varPoints[4];
        auto &varP0=varPoints[0];
        auto &varP1=varPoints[1];
        auto &varP2=varPoints[2];
        auto &varP3=varPoints[3];
        auto *varPStart=&varP0;
        auto *varPEnd=varPStart+4;
        for (const auto &varI:varAns) {

            const auto &varStartPoint=varContour[varI[0]];
            varP0.rx()=varStartPoint.x; varP3.rx()=varStartPoint.x;
            varP0.ry()=varStartPoint.y; varP3.ry()=varStartPoint.y;

            const auto &varEndPoint=varContour[varI[1]];
            varP1.rx()=varEndPoint.x;
            varP1.ry()=varEndPoint.y;

            const auto &varFarPoint=varContour[varI[2]];
            varP2.rx()=varFarPoint.x;
            varP2.ry()=varFarPoint.y;

            auto varSeries=addLineSeries(varChartImage,varPStart,varPEnd);

            varSeries->setPointsVisible(true);

        }
    }

    this->addWidget(varImageShowWidget.release())->resize(800,600);
    varImageShowWidget->setOriginalImageWidgetVisible(false);
    return varImageShowWidget;
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
    return nullptr;
}

void MainWindow::openLua() {
    //cv::convexityDefects()
    return _Super::openLua();
}

/*End of the file.*/

