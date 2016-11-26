/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "RGBADialog.hpp"
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
        using DialogType=RGBADialog;
        auto image=arg.convertToFormat(QImage::Format_RGBA8888);
        this->setImage(image);
        using namespace memory;
        auto && dialog=makeStackPointer<DialogType>();
        this->addImageWidget(dialog.release());
        connect(dialog.pointer(),&DialogType::valueChanged,
            this,&ImageWidget::valueChanged);
        dialog->emitValueChanged();
    }

    void valueChanged(
        double RAlpha,
        double RBeta,
        double GAlpha,
        double GBeta,
        double BAlpha,
        double BBeta,
        double AAlpha,
        double ABeta) {
        this->setAlgorithm([=](const QImage &arg)->QImage {

            try {
                auto image=arg.copy();

                cv::Mat inputMat(image.height(),image.width(),
                    CV_8UC4,const_cast<uchar*>(image.constBits()),
                    image.bytesPerLine());
                cv::Mat outputMat;

                cv::Mat rgbaMat[4];

                cv::split(inputMat,rgbaMat);

                for (auto & m:rgbaMat) {
                    m.convertTo(m,CV_64FC1);
                }

                rgbaMat[0]=RAlpha*rgbaMat[0]+RBeta;
                rgbaMat[1]=GAlpha*rgbaMat[1]+GBeta;
                rgbaMat[2]=BAlpha*rgbaMat[2]+BBeta;
                rgbaMat[3]=AAlpha*rgbaMat[3]+ABeta;

                cv::merge(rgbaMat,4,outputMat);
                outputMat.convertTo(inputMat,CV_8UC4);

                return std::move(image);

            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }

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

