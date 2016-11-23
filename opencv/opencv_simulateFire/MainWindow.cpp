/*MainWindow.cpp*/
#include "MainWindow.hpp"
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

/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    return _Super::addImage(arg);
}

namespace {

void add_image(MainWindow *view)try {

    constexpr auto rows=1024;
    constexpr auto cols=1024;

    cv::Mat mat=cv::Mat::zeros(rows,cols,CV_64FC1);

    {
        auto p=reinterpret_cast<double*>(mat.ptr(0));
        for (auto i=0; i<cols; ++i,++p) {
            *p+=(std::rand()&1023)/1024.0;
        }
    }

    for(int k=0;k<200;++k)
    {
        auto cp=mat.ptr(0);
        for (int i=1; i<(rows-1); ++i) {
            auto lp=reinterpret_cast<double*>(cp)+1;
            cp+=mat.step;
            auto p=reinterpret_cast<double*>(cp)+1;
            for (int j=1; j<(cols-1);++j,++p,++lp) {
                *p+=(*(lp-1)+(*lp)+*(lp+1));
                *p/=4;
            }
        }
    }

    cv::normalize(
        mat,mat,
        255.0,0.0,
        cv::NORM_MINMAX,
        CV_8UC1);

    QOpencvImage image;
    image.fromOpencvMat(mat);

    view->addImage(image);
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

}/*namespace*/


class FireImageShowWidget :public ImageShowWidget {
    cv::Mat fireData;
    QImage fireImage;
    int fireTimerID=0;
    constexpr static auto rows=1024;
    constexpr static auto cols=1024;
public:
    FireImageShowWidget() {
        fireData=cv::Mat::zeros(rows,cols,CV_64FC1);
        fireImage=QImage(cols,rows,QImage::Format_Grayscale8);
        /*init first line*/
        auto p=reinterpret_cast<double*>(fireData.data);
        auto pend=p+cols;
        for (; p<pend;++p) {
            *p+=(std::rand()&1023)/1024.0;
        }

        fireTimerID=this->startTimer(1000);
        setOriginalImageWidgetVisible(false);
    }

    void timerEvent(QTimerEvent *e)override {
        if (e->timerId()==fireTimerID) { updateFireView(); }
    }

    void updateFireView(){

        /*更新数据*/
        auto data_p=fireData.data;
        for (int i=1; i<(rows-1); ++i) {
            /*上一行的指针*/
            auto last_p=reinterpret_cast<double*>(data_p)+1;
            /*更新数据指针*/
            data_p+=fireData.step;
            /*当前行的指针*/
            auto p=reinterpret_cast<double*>(data_p)+1;
            for (int j=1; j<(cols-1);++j,++p,++last_p) {
                *p+=(*(last_p-1)+(*last_p)+*(last_p+1));
                (*p)*=(1/4.008);
            }
        }

        cv::Mat mat(rows,cols,CV_8UC1,
            fireImage.bits(),fireImage.bytesPerLine());

        cv::normalize(
            fireData,mat,
            255.0,0.0,
            cv::NORM_MINMAX,
            CV_8UC1);

        cv::flip(mat,mat,0);

        this->setImage(fireImage);
    }

private:
    CPLUSPLUS_OBJECT(FireImageShowWidget)
};

void MainWindow::openLua() {
    this->addWidget(new FireImageShowWidget);
}

/*End of the file.*/

