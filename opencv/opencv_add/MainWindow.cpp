/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>

class MainWindow::_PrivateMainWindow {
    using ImageShowWidgetPointer=ImageShowWidget *;
    ImageShowWidgetPointer /*⒨*/\u24A8CurrentImageShowWidget=nullptr;
public:
    inline auto * getCurrentImageShowWidget() { return this->/*⒨*/\u24A8CurrentImageShowWidget; }
    inline void setCurrentImageShowWidget(ImageShowWidgetPointer arg) { this->/*⒨*/\u24A8CurrentImageShowWidget=arg; }
    inline const auto * getCurrentImageShowWidget() const { return this->/*⒨*/\u24A8CurrentImageShowWidget; }
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
    if (addImageIndex()<0/*the last*/) {
        auto varAns=_thisp->getCurrentImageShowWidget();
        if (varAns==nullptr) { return nullptr; }

        varAns->setAlgorithm([varImages=varAns->getImages()]
        (const QImage &arg)->QImage{

            if (varImages.size()<2) { return arg; }

            /*将图片调整到同一大小*/
            QSize varMaxSize;
            for (auto & varI:varImages) {
                auto varSize=varI->size();
                varMaxSize.setHeight(
                    std::max(varMaxSize.height(),varSize.height()));
                varMaxSize.setWidth(
                    std::max(varMaxSize.width(),varSize.width()));
            }

            std::vector<cv::Mat,memory::Allocator<cv::Mat>> argImages;
            argImages.reserve(varImages.size());

            try {
                for (auto & varI:varImages) {
                    if (varI->size()==varMaxSize) {
                        /*使用引用节省内存*/
                        cv::Mat var(varI->height(),
                            varI->width(),
                            CV_8UC4,
                            const_cast<uchar*>(varI->constBits()),
                            varI->bytesPerLine());
                        argImages.push_back(var);
                    }
                    else {
                        /*resize图片*/
                        cv::Mat var(varI->height(),
                            varI->width(),
                            CV_8UC4,
                            const_cast<uchar*>(varI->constBits()),
                            varI->bytesPerLine());
                        cv::Mat varAns;
                        cv::resize(var,varAns,
                            cv::Size(varMaxSize.width(),varMaxSize.height()),
                            0.,0.,cv::INTER_LANCZOS4);
                        argImages.push_back(std::move(varAns));
                    }
                }
            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
                return arg;
            }

            try {

                //std::vector<cv::Mat> argImages/*图片*/;
                //QSize varMaxSize/*图片大小*/;
                const auto varHeight=varMaxSize.height();
                const auto varWidth=varMaxSize.width();

                /*为结果图片预分配内存*/
                QImage varImageAns(varWidth,varHeight,QImage::Format_RGBA8888);
                cv::Mat varImageAnsWrap(varHeight,varWidth,
                                        CV_8UC4,
                                        const_cast<uchar*>(varImageAns.constBits()),
                                        varImageAns.bytesPerLine()
                );

                {/*生成图片*/
                    cv::Mat varAns=cv::Mat::zeros(varHeight,varWidth,CV_32FC4);
                    for (const auto & varI:argImages) {
                        cv::add(varAns,varI,varAns,{},CV_32FC4);
                    }
                    /*结果归一化*/
                    cv::normalize(varAns,varAns,255,0,cv::NORM_MINMAX);
                    varAns.convertTo(varImageAnsWrap,varImageAnsWrap.type());
                }

                {/*进行直方图均值化*/
                    argImages.clear();
                    argImages.resize(4);
                    cv::split(varImageAnsWrap,argImages.data());
                    for (auto & varI:argImages) {
                        cv::equalizeHist(varI,varI);
                    }
                    cv::merge(argImages.data(),4,varImageAnsWrap);
                }

                return std::move(varImageAns);
            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }
            return arg;
        });

        _thisp->setCurrentImageShowWidget(nullptr);
        return varAns;
    }
    else if (addImageIndex()==1/*the first*/) {
        if (_thisp->getCurrentImageShowWidget()==nullptr) {
            if (arg.isNull()) { return nullptr; }
            using namespace memory;
            auto && widget=makeStackPointer<ImageShowWidget>();
            widget->setImage(arg.convertToFormat(QImage::Format_RGBA8888));
            this->addWidget(widget.release());
            _thisp->setCurrentImageShowWidget(widget);
        }
        return nullptr;
    }
    else if (addImageIndex()==0/*just a image*/) {
        return nullptr;
    }
    else {
        auto varImageShow=_thisp->getCurrentImageShowWidget();
        if (varImageShow==nullptr) { return nullptr; }
        if (arg.isNull()) { return nullptr; }
        using namespace memory;
        auto && view=makeStackPointer<PlainImageView>();
        varImageShow->addImageWidget(view.release());
        view->setImage(arg.convertToFormat(QImage::Format_RGBA8888));
        return nullptr;
    }
}

void MainWindow::openLua() {
    return _Super::openLua();
}

/*End of the file.*/

