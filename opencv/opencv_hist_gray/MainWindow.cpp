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

/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    if(arg.isNull()){return nullptr;}
    auto varImage=arg.convertToFormat( QImage::Format_Grayscale8 );

    return nullptr;
}

void MainWindow::openLua(){
    return _Super::openLua();
}

/*End of the file.*/

