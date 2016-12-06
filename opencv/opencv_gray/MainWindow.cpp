/*MainWindow.cpp*/
#include "MainWindow.hpp"
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

    void valueChanged(double /* RAlpha */ ,
                      double /* RBeta */ ,
                      double /* GAlpha */ ,
                      double /* GBeta */ ,
                      double /* BAlpha */ ,
                      double /* BBeta */){

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

