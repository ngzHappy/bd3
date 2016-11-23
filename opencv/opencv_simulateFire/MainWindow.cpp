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
class FireImageShowWidget :public ImageShowWidget {
    cv::Mat fireData;
    QImage fireImage;
    int fireTimerID=0;
    double control=0;
    constexpr static auto rows=300;
    constexpr static auto cols=512;
    static_assert(rows>256,"");
public:
    FireImageShowWidget() {

        fireData=cv::Mat::zeros(rows,cols,CV_64FC1);
        fireImage=QImage(cols,rows,QImage::Format_RGBA8888);

        fireTimerID=this->startTimer(1000/20);
        setOriginalImageWidgetVisible(false);

        {
            /*init first line*/
            auto p=reinterpret_cast<double*>(fireData.data);
            auto pend=p+cols;
            for (; p<pend; ++p) {
                *p=std::max(.512,std::min(.9915,(std::rand()&1023)/(512.)));
            }

        }

        updateFireView();

    }

    void timerEvent(QTimerEvent *e)override {
        if (e->timerId()==fireTimerID) {
            control+=0.05;
            if (control>1) { control=0; }
            updateFireView();
        }
    }

    void updateFireView() {

        double not_used=0;
        /*更新数据*/
        auto data_p=fireData.data;
        for (int i=1; i<(rows-1); ++i) {
            /*上一行的指针*/
            auto last_p=reinterpret_cast<double*>(data_p)+1;
            /*更新数据指针*/
            data_p+=fireData.step;
            /*当前行的指针*/
            auto p=reinterpret_cast<double*>(data_p)+1;
            for (int j=1; j<(cols-1); ++j,++p,++last_p) {

                /*control 控制偏向*/
                *p+=(*(last_p-1))+
                    (*last_p)+
                    (*(last_p+1))+
                    .5*(1-control)*(*(p+1))+
                    .5*control*(*(p-1));

                (*p)*=(1./(.5+4-.025));

                /*进行数据裁剪到[0-1]*/
                *p=std::modf(*p,&not_used);

            }
        }

        cv::Mat mat;

        fireData.convertTo(mat,CV_8UC1,255);

        cv::flip(mat,mat,0);

        cv::applyColorMap(mat,mat,cv::COLORMAP_JET);
        cv::Mat rgbaMat(
            fireImage.height(),
            fireImage.width(),
            CV_8UC4,
            const_cast<uchar *>(fireImage.constBits()),
            fireImage.bytesPerLine());

        cv::cvtColor(mat,rgbaMat,cv::COLOR_BGR2RGBA);

        this->setImage(fireImage);

        /*
        使用ROI进行裁剪
        加速衰减
        */
        fireData.rowRange(cv::Range(256,rows-1))=cv::Scalar(0,0,0,0);
        fireData.rowRange(cv::Range(200,256))*=0.97+(rand()&1023)/102400.0;
        fireData.rowRange(cv::Range(128,200))*=0.98+(rand()&1023)/102400.0;
        fireData.rowRange(cv::Range(64,128))*=0.99+(rand()&1023)/102400.0;

    }

private:
    CPLUSPLUS_OBJECT(FireImageShowWidget)
};

}

void MainWindow::openLua() {
    this->addWidget(new FireImageShowWidget);
}

/*End of the file.*/

