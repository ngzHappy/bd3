/*MainWindow.cpp*/
#include <cmath>
#include "MainWindow.hpp"
#include "VortexDialog.hpp"
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

namespace {

class ImageWidget : public ImageShowWidget {
public:
    ImageWidget(const QImage &arg) {
        using DialogType=VortexDialog;
        auto image = arg.convertToFormat(QImage::Format_RGB888);
        this->setImage(image);
        using namespace memory;
        auto && dialog=makeStackPointer<DialogType>();
        this->addImageWidget(dialog.release());
        connect(dialog.pointer(),&DialogType::valueChanged,
            this,&ImageWidget::valueChanged);
        dialog->emitValueChanged();
    }

    void valueChanged(int /* changeCount */) {

        this->setAlgorithm([=](const QImage &arg)->QImage {
            try {

                cv::Mat inputMat(arg.height(),arg.width(),CV_8UC3,
                    const_cast<uchar*>(arg.constBits()),
                    arg.bytesPerLine());

                /*copy the image*/
                QImage ans=arg.copy();
                cv::Mat outputMat(
                    ans.height(),ans.width(),CV_8UC3,
                    const_cast<uchar*>(ans.constBits()),
                    ans.bytesPerLine()
                );

                using number_type=double;
                const auto width=arg.width();
                const auto height=arg.height();
                const number_type center_x=width/2.;
                const number_type center_y=height/2.;

                /*(x,y)是变换后的点坐标*/
                for (auto y=0; y<height;++y ) {
                    for (auto x=0; x<width;++x) {
                        
                        auto dy=y-center_y;
                        auto dx=x-center_x;

                        /*不动点*/
                        if ((dx==0)&&(dy==0)) { 
                            continue;
                        }

                        /*化为极坐标*/
                        /*求出偏角*/
                        auto th=std::atan2(dy,dx);
                        /*求p*/
                        auto dis=std::sqrt(dx*dx+dy*dy);

                        /*求出偏转角度*/
                        th-=dis/50;

                        /*求出原来的坐标*/
                        dx= dis*std::cos(th)+center_x ;
                        dy= dis*std::sin(th)+center_y ;

                        /*设置颜色*/
                        if ((dx<width)&&(dy<height)&&(dx>0)&&(dy>0)) {
                            const auto & oColor=inputMat.at<cv::Vec3b>(dy,dx);

                            outputMat.at<cv::Vec3b>(y,x)=oColor;
                        }
                        

                    }
                }

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

void MainWindow::openLua(){
    return _Super::openLua();
}

/*End of the file.*/

