/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>
#include "OldPictureDialog.hpp"

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
    ImageWidget(const QImage &arg) {
        auto image=arg.convertToFormat(QImage::Format_RGB888);
        this->setImage(image);
        using namespace memory;
        auto && dialog=makeStackPointer<OldPictureDialog>();
        this->addImageWidget(dialog.release());
        connect(dialog.pointer(),&OldPictureDialog::valueChanged,
            this,&ImageWidget::valueChanged);
        dialog->emitValueChanged();
    }

    void valueChanged(double blendValue) {

        /*  老照片效果
         *
         *       0.393,0.769,0.189
         *  A =  0.349,0.686,0.168
         *       0.272,0.534,0.131
         *
         *  p(x,y)=(blendValue)*A*p(x,y)+(1-blendValue)*p(x,y)
        */
        this->setAlgorithm([=](const QImage &arg)->QImage {

            try {
                cv::Mat imageInput(arg.height(),arg.width(),CV_8UC3,
                                   const_cast<uchar*>(arg.constBits()),
                                   arg.bytesPerLine());

                cv::Mat ansMat;

                {
                    /*准备临时数据*/
                    cv::Mat rgb[6];

                    /*转型*/
                    imageInput.convertTo(rgb[5],CV_32FC3);

                    /*分割rgb通道*/
                    cv::split(rgb[5],rgb);

                    /*保存原始图像数据*/
                    imageInput=rgb[5];

                    /*分开计算 A * p */
                    rgb[3]=0.393f*rgb[0]+0.769f*rgb[1]+0.189f*rgb[2];
                    rgb[4]=0.349f*rgb[0]+0.686f*rgb[1]+0.168f*rgb[2];
                    rgb[5]=0.272f*rgb[0]+0.534f*rgb[1]+0.131f*rgb[2];

                    /*合成  A * p */
                    cv::merge(&rgb[3],3,rgb[0]);

                    /*计算 blendValue * A * p + (1-blendValue) * p */
                    rgb[1]=static_cast<float>(blendValue) * rgb[0]
                        +static_cast<float>(1-blendValue) * imageInput;

                    ansMat=std::move(rgb[1]);

                }

                QImage ans(ansMat.cols,ansMat.rows,QImage::Format_RGB888);
                cv::Mat ansWrap(ans.height(),ans.width(),CV_8UC3,
                                const_cast<uchar*>(ans.constBits()),
                                ans.bytesPerLine());

                ansMat.convertTo(ansWrap,CV_8UC3);

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

