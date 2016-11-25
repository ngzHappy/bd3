/*MainWindow.cpp*/
#include <vector>
#include <cassert>
#include "MainWindow.hpp"
#include "JpegNDialog.hpp"
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

class ImageWidget :public ImageShowWidget {
public:
    ImageWidget(const QImage & arg) {
        QImage image=arg.convertToFormat(QImage::Format_RGB888);
        this->setImage(image);
        using namespace memory;
        auto && dialog=makeStackPointer<JpegNDialog>();
        this->addImageWidget(dialog.release());
        connect(dialog.pointer(),&JpegNDialog::valueChanged,
            this,&ImageWidget::valueChanged);
        dialog->emitValueChanged();
    }

    void valueChanged(int changeCount) {

        this->setAlgorithm([=](const QImage & arg)->QImage {
            if (changeCount<1) { return arg; }
            auto i=changeCount;

            try {

                QImage image=arg.copy();
                auto imageData=const_cast<uchar*>(image.constBits());
                auto lineStep=image.bytesPerLine();
                auto imageHeight=image.height();
                auto imageWidth3=image.width()*3;
                auto lineEnd=imageData+imageHeight*lineStep;
                std::vector<std::uint8_t> buffer;

                std::vector<int> par={
                    CV_IMWRITE_JPEG_QUALITY,75,
                };
                cv::Mat input(imageHeight,image.width(),CV_8UC3,
                    imageData,lineStep);

                /*opencv架构级错误，导致大量无用运算*/
                cv::cvtColor(input,input,cv::COLOR_RGB2BGR);

                /*参考:*/
                /*view-source:https://m13253.github.io/JPEGreen/*/

                auto clamp=[](const auto & x)->std::uint8_t {
                    return (x>=0)?(x<=255)?
                        std::uint8_t(x):std::uint8_t(255)
                        :std::uint8_t(0);
                };

                auto clampuv=[](const auto & x)->std::int8_t {
                    return (x>=-128)?(x<=127)?
                        std::int8_t(x):std::int8_t(127)
                        :std::int8_t(-128);
                };

                while ((--i)>=0) {

                    /*RGB 与 YUV 低精度转换*/
                    auto line=imageData;
                    for (; line<lineEnd; line+=lineStep) {
                        auto p=line; auto pend=p+imageWidth3;
                        for (; p<pend; p+=3) {

                            const auto &b=p[0];
                            const auto &g=p[1];
                            const auto &r=p[2];

                            const auto y=clamp((77*r+150*g+29*b)>>8);
                            const auto u=clampuv(((-43*r-85*g+128*b)>>8)-1);
                            const auto v=clampuv(((128*r-107*g-21*b)>>8)-1);

                            p[0]=clamp((65536*y+91881*v)>>16);
                            p[1]=clamp((65536*y-22553*u-46802*v)>>16);
                            p[2]=clamp((65536*y+116130*u)>>16);

                        }
                    }

                    /*opencv架构级别错误，导致大量无用运算，
                    尤其是save/load图片过程中，第三方库一般是按照rgb设计的，
                    于是opencv要先将bgr转rgb，浪费大量时间
                    可以自行查看opencv源代码验证*/
                    cv::imencode(".jpeg",input,buffer,par);
                    input=cv::imdecode(buffer,CV_LOAD_IMAGE_COLOR,&input);

                    assert(imageData==input.data);
                }

                /*opencv架构级错误，导致大量无用运算*/
                cv::cvtColor(input,input,cv::COLOR_RGB2BGR);

                return std::move(image);
            }
            catch (...) { CPLUSPLUS_EXCEPTION(false); }
            return arg;
        });

    }

private:
    CPLUSPLUS_OBJECT(ImageWidget)
};

}/*namespace*/

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

