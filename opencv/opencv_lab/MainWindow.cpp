/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "LABDialog.hpp"
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
        using DialogType=LABDialog;
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
        double LAlpha,
        double LBeta,
        double AAlpha,
        double ABeta,
        double BAlpha,
        double BBeta) {
        this->setAlgorithm([=](const QImage & arg)->QImage {

            try {
                auto image=arg.convertToFormat(QImage::Format_RGB888);

                cv::Mat inputMat(image.height(),image.width(),
                    CV_8UC3,const_cast<uchar*>(image.constBits()),
                    image.bytesPerLine());

                cv::Mat outputMat;
                cv::cvtColor(inputMat,outputMat,cv::COLOR_RGB2Lab,CV_32FC3);

                cv::Mat labMat[3];
                cv::split(outputMat,labMat);

                labMat[0]=LAlpha*labMat[0]+LBeta;
                labMat[1]=AAlpha*labMat[1]+ABeta;
                labMat[2]=BAlpha*labMat[2]+BBeta;

                cv::merge(labMat,3,outputMat);

                cv::cvtColor(outputMat,outputMat,cv::COLOR_Lab2RGB);
                outputMat.convertTo(inputMat,CV_8UC3);

                return std::move(image);

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

