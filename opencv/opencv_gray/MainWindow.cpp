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

               auto & /*⓵*/\u24f5=varRGB[0];
               auto & /*⓶*/\u24f6=varRGB[1];
               auto & /*⓷*/\u24f7=varRGB[2];
               auto & /*⓸*/\u24f8=varRGB[3];

                cv::split(varInputImage,varRGB);

                /*⓵*/\u24f5.convertTo(/*⓸*/\u24f8,CV_32FC1);
                /*⓵*/\u24f5=/*⓸*/\u24f8.clone();
                /*⓶*/\u24f6.convertTo(/*⓸*/\u24f8,CV_32FC1);
                /*⓶*/\u24f6=/*⓸*/\u24f8.clone();
                /*⓷*/\u24f7.convertTo(/*⓸*/\u24f8,CV_32FC1);
                /*⓷*/\u24f7=/*⓸*/\u24f8;

                /*⓵*/\u24f5*=RAlpha;
                /*⓶*/\u24f6*=GAlpha;
                /*⓷*/\u24f7*=BAlpha;

                /*⓸*/\u24f8=/*⓷*/\u24f7+/*⓶*/\u24f6+/*⓵*/\u24f5+RGBBeta;

                QImage varAns(arg.size(),QImage::Format_Grayscale8);
                /*⓵*/\u24f5=cv::Mat(varAns.height(),varAns.width(),
                    CV_8UC1,
                    const_cast<uchar*>(varAns.constBits()),
                    varAns.bytesPerLine());
                /*⓸*/\u24f8.convertTo(/*⓵*/\u24f5,CV_8UC1);

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

