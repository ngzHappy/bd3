/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>
#include "ApproxPolyDPDialog.hpp"

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
    return _Super::addImage(arg);
}

namespace {

class DataWidget :public ImageShowWidget {

public:
    DataWidget( ) {

    }

    void valueChanged(double ) {



    }

private:
    CPLUSPLUS_OBJECT(ImageWidget)
};

}/*namespace*/

void MainWindow::openLua(){
    auto varPoints = qApp->getPoint2d();
    auto varRows=varPoints.second-varPoints.first;
    if(varRows < 2){ return ; }
}

/*End of the file.*/


