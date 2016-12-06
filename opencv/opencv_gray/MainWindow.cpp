/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "GrayDialog.hpp"
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

class ImageWidget :public ImageShowWidget {
public:
    ImageWidget(const QImage & arg) {
        using DialogType=GrayDialog;
        auto image=arg.convertToFormat(QImage::Format_RGB888);
        this->setImage(image);
        using namespace memory;
        auto && dialog=makeStackPointer<DialogType>();
        this->addImageWidget(dialog.release());
        connect(dialog.pointer(),&DialogType::valueChanged,
                this,&ImageWidget::valueChanged);
        dialog->emitValueChanged();
    }

    void valueChanged(double RAlpha,
                      double GAlpha,
                      double BAlpha,
                      double RGBBeta){
        this->setAlgorithm([=](const QImage & arg)->QImage{
            try{

                cv::Mat varInputImage(arg.height(),arg.width(),
                    CV_8UC3,
                    const_cast<uchar*>(arg.constBits()),
                    arg.bytesPerLine());

                cv::Mat varRGB[4];

               auto & var0=varRGB[0];
               auto & var1=varRGB[1];
               auto & var2=varRGB[2];
               auto & var3=varRGB[3];

                cv::split(varInputImage,varRGB);

                var0.convertTo(var3,CV_32FC1);
                var0=var3.clone();
                var1.convertTo(var3,CV_32FC1);
                var1=var3.clone();
                var2.convertTo(var3,CV_32FC1);
                var2=var3;

                var0*=RAlpha;
                var1*=GAlpha;
                var2*=BAlpha;

                var3=var2+var1+var0+RGBBeta;

                QImage varAns(arg.size(),QImage::Format_Grayscale8);
                var0=cv::Mat(varAns.height(),varAns.width(),
                    CV_8UC1,
                    const_cast<uchar*>(varAns.constBits()),
                    varAns.bytesPerLine());
                var3.convertTo(var0,CV_8UC1);

                return std::move(varAns);

            }catch(...){
                CPLUSPLUS_EXCEPTION(false);
            }
            return arg;
        });
    }

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

