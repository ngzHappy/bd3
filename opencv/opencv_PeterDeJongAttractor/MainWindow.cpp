/*MainWindow.cpp*/
#include <cmath>
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

void add_image(MainWindow *view) try {

    constexpr auto rows=1024;
    constexpr auto cols=1024;
    constexpr auto posx_max=cols-1;
    constexpr auto posy_max=rows-1;
    constexpr double step_x=cols/(2.-(-2.));
    constexpr double step_y=rows/(2.-(-2.));

    /*点出现概率的统计矩阵*/
    cv::Mat hist=cv::Mat::zeros(rows,cols,CV_64FC1);

    /* 设置初始化值 */
    constexpr auto a=-12.7;
    constexpr auto b=-1.09;
    constexpr auto c=-.816;
    constexpr auto d=-2.12;
    auto x=20.1111242432;
    auto y=564.447152;

    /*迭代生成图片*/
    for (int k=0; k<10; ++k)
        for (int i=0; i<(1024*1024); ++i) {

            auto xn=std::sin(a*y)-std::cos(b*x);
            auto yn=std::sin(c*x)-std::cos(d*y);

            auto posx=static_cast<int>(std::max(0.0,(xn+2)*step_x));
            auto posy=static_cast<int>(std::max(0.0,(yn+2)*step_y));

            posx=std::min(posx,posx_max);
            posy=std::min(posy,posy_max);

            auto &currentHist=hist.at<double>(posy,posx);
            ++currentHist;

            x=xn;
            y=yn;

        }

    /*分配灰度图内存*/
    QImage ansGray(cols,rows,QImage::Format_Grayscale8);
    /*对灰度图内存的引用*/
    cv::Mat matGray(ansGray.height(),ansGray.width(),
        CV_8UC1,ansGray.bits(),ansGray.bytesPerLine());
    /*将统计图归一化到[0,255],生成灰度图*/
    cv::normalize(
        hist,matGray,
        255.0,0.0,
        cv::NORM_MINMAX,
        CV_8UC1);
    /*直方图归一化*/
    cv::equalizeHist(matGray,matGray);

    /*将灰度图加入图片到绘制体系*/
    view->addImage(ansGray);

    /*分配彩色图内存*/
    QImage ansRGB(cols,rows,QImage::Format_RGB888);
    ansRGB.fill(QColor(0,0,0,255));

    /*引用彩色图片内存*/
    cv::Mat matRGB(ansRGB.height(),ansRGB.width(),
        CV_8UC3,ansRGB.bits(),ansRGB.bytesPerLine());

    /*灰度图重映射*/
    cv::applyColorMap(matGray,matRGB,cv::COLORMAP_COOL);

    /*将opencv bgr色系转为rgb色系(opencv架构级错误,默认用bgr而不是rgb)*/
    cv::cvtColor(matRGB,matRGB,cv::COLOR_BGR2RGB);

    /*将灰度图加入图片到绘制体系*/
    view->addImage(ansRGB);
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

}/*namespace*/

void MainWindow::openLua() {
    add_image(this);
}

/*End of the file.*/

