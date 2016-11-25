/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "ResizeDialog.hpp"
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
        QImage inputImage=arg.convertToFormat(QImage::Format_RGBA8888);
        this->setImage(inputImage);
        using namespace memory;
        auto && dialog=makeStackPointer<ResizeDialog>();
        connect(dialog.pointer(),&ResizeDialog::valueChanged,
            this,&ImageWidget::valueChanged);
        this->addImageWidget(dialog.release());
        dialog->emitValueChanged();
    }
    
    void valueChanged(
        int width,
        int height,
        double fx,
        double fy,
        int interpolation) {

        this->setAlgorithm([=](const QImage &arg)->QImage {
            try {
                cv::Mat input(arg.height(),arg.width(),CV_8UC4,
                   const_cast<uchar*>(arg.bits()),arg.bytesPerLine());
                cv::Mat output;
                cv::resize(input,output,{width,height},fx,fy,interpolation);
                QImage outputImage(output.data,
                    output.cols,output.rows,output.step,
                    QImage::Format_RGBA8888);
                return outputImage.copy();
            }
            catch (...) { CPLUSPLUS_EXCEPTION(false); }
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
    this->addWidget(new ImageWidget(arg));
}

void MainWindow::openLua() {
    return _Super::openLua();
}

/*End of the file.*/

