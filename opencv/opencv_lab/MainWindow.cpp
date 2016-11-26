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
    return _Super::addImage(arg);
}

void MainWindow::openLua() {
    return _Super::openLua();
}

/*End of the file.*/

