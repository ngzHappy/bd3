/*MainWindow.cpp*/
#include <cmath>
#include "MainWindow.hpp"
#include "VortexDialog.hpp"
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

namespace {

class ImageWidget : public ImageShowWidget {
public:
    ImageWidget(const QImage &arg) {
        using DialogType=VortexDialog;
        auto image=arg.convertToFormat(QImage::Format_RGB888);
        this->setImage(image);
        using namespace memory;
        auto && dialog=makeStackPointer<DialogType>();
        this->addImageWidget(dialog.release());
        connect(dialog.pointer(),&DialogType::valueChanged,
            this,&ImageWidget::valueChanged);
        dialog->emitValueChanged();
    }

    void valueChanged(double radius,double rate) {

        this->setAlgorithm([rate_=rate,
                radius,
                this
        ](const QImage &arg)->QImage {

            if (rate_<.00000001) { return arg; }
            if (radius<1.00000001) { return arg; }
            auto rate=1.0/rate_;

            try {

                cv::Mat inputMat(arg.height(),arg.width(),CV_8UC3,
                    const_cast<uchar*>(arg.constBits()),
                    arg.bytesPerLine());

                /*copy the image*/
                QImage ans={ arg.size(),arg.format() };
                cv::Mat outputMat(
                    ans.height(),ans.width(),CV_8UC3,
                    const_cast<uchar*>(ans.constBits()),
                    ans.bytesPerLine()
                );

                cv::Mat mapX(ans.height(),ans.width(),CV_32FC1);
                cv::Mat mapY(ans.height(),ans.width(),CV_32FC1);

                using number_type=double;
                const auto width=arg.width();
                const auto height=arg.height();
                const number_type center_x=width/2.;
                const number_type center_y=height/2.;

                /*(x,y)是变换后的点坐标*/
                for (auto y=0; y<height; ++y) {
                    for (auto x=0; x<width; ++x) {

                        auto dy=y-center_y;
                        auto dx=x-center_x;
                        number_type th,dis;

                        /*不动点*/
                        if ((dx==0)&&(dy==0)) {
                            goto not_changed;
                        }

                        /*化为极坐标*/
                        /*求出偏角*/
                        th=std::atan2(dy,dx);
                        /*求p*/
                        dis=std::sqrt(dx*dx+dy*dy);

                        if (dis>radius) {
                        not_changed:
                            mapX.at<float>(y,x)=x;
                            mapY.at<float>(y,x)=y;
                            continue;
                        }

                        /*求出偏转角度*/
                        {
                            auto tmp=std::log(std::abs(dis*rate)+1.0001);
                            tmp*=tmp;
                            th+=tmp;
                        }
                        /*求出原来的坐标*/
                        dx=dis*std::cos(th)+center_x;
                        dy=dis*std::sin(th)+center_y;

                        /*设置变换矩阵*/
                        mapX.at<float>(y,x)=static_cast<float>(dx);
                        mapY.at<float>(y,x)=static_cast<float>(dy);

                    }
                }

                cv::remap(inputMat,outputMat,mapX,mapY,
                    cv::INTER_LANCZOS4,
                    cv::BORDER_REPLICATE);

                return std::move(ans);

            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }
            return arg;
        });

    }

private:
    CPLUSPLUS_OBJECT(ImageWidget)
};

}/*namespace*/

/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    if (arg.isNull()) { return nullptr; }
    auto ans=new ImageWidget(arg);
    this->addWidget(ans);
    return ans;
}

void MainWindow::openLua() {
    return _Super::openLua();
}

/*End of the file.*/

