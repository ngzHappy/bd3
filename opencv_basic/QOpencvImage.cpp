#include "QOpencvImage.hpp"
#include <private/qimage_p.h>

/************************************************************************/
/*构造函数*/
QOpencvImage::~QOpencvImage() {
}
QOpencvImage::QOpencvImage() {
}
QOpencvImage::QOpencvImage(const QOpencvImage&arg):_Super(arg) {
}
QOpencvImage::QOpencvImage(QOpencvImage&&arg):
    _Super(std::move(std::move(arg)._p_getImage())) {
}
QOpencvImage::QOpencvImage(const QImage&arg):_Super(arg) {
}
QOpencvImage::QOpencvImage(QImage&&arg):_Super(std::move(arg)) {
}

/************************************************************************/

/*
创建opencv数据,
进行浅拷贝,
可能会早成QImage格式变换,
不要令此数据脱离函数栈区
*/
cv::Mat QOpencvImage::_p_toOpencvRef() {
    if (this->isNull()) { return{}; }

    int varHasRun=0;
run_again:
    if (varHasRun>1) { return{}; }

    const QImage & cThis=*this/**/;
    QImage::Format varFormat=cThis.format();

    switch (varFormat) {
        case QImage::Format_Invalid:return{};
        case QImage::Format_Mono: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_MonoLSB: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_Indexed8: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_RGB32: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGB888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_ARGB32: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_ARGB32_Premultiplied: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_RGB16: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGB888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_ARGB8565_Premultiplied: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_RGB666: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGB888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_ARGB6666_Premultiplied: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_RGB555: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGB888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_ARGB8555_Premultiplied: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_RGB888: {/*!!!*/
            return cv::Mat(cThis.height(),cThis.width(),
                CV_8UC3,
                const_cast<uchar *>(cThis.constBits()),
                cThis.bytesPerLine());
        }
        case QImage::Format_RGB444: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGB888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_ARGB4444_Premultiplied: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_RGBX8888: {/*same as QImage::Format_RGBA8888*/}
        case QImage::Format_RGBA8888: {/*RGBA8888*/
            return cv::Mat(cThis.height(),cThis.width(),
                CV_8UC4,
                const_cast<uchar *>(cThis.constBits()),
                cThis.bytesPerLine());
        }
        case QImage::Format_RGBA8888_Premultiplied: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_BGR30:{
            QImage::operator=(this->convertToFormat(QImage::Format_RGB888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_A2BGR30_Premultiplied: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_RGB30: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGB888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_A2RGB30_Premultiplied: {
            QImage::operator=(this->convertToFormat(QImage::Format_RGBA8888));
            ++varHasRun;
            goto run_again;
        }
        case QImage::Format_Alpha8:return{/*???*/ };
        case QImage::Format_Grayscale8: {/*灰度图*/
            return cv::Mat(cThis.height(),cThis.width(),
                CV_8UC1,
                const_cast<uchar *>(cThis.constBits()),
                cThis.bytesPerLine());
        }
        case QImage::NImageFormats:return{/*???*/ };
        default:break;
    }

    return{};
}

/*进行深拷贝*/
QOpencvImage & QOpencvImage::fromOpencvMat(const cv::Mat &arg) {
    
    do {
        if ((arg.rows<1)||(arg.cols<1)) { break; }
        bool varIsThis=false;
        const auto varChannels=arg.channels();
        if (varChannels==1) {
            /*分配内存*/
            QImage _tmp;
            if ((this->format()==QImage::Format_Grayscale8)&&
                (this->height()==arg.rows)&&
                (this->width()==arg.cols)&&
                (this->data_ptr()->own_data)) {
                this->detach();
                _tmp=*this;
                varIsThis=true;
            }
            else { 
                _tmp=QImage{ arg.cols,arg.rows,QImage::Format_Grayscale8 };
            }
            /*设置包装*/
            cv::Mat var(_tmp.height(),_tmp.width(),
                CV_8UC1,
                const_cast<uchar *>(_tmp.constBits()),
                _tmp.bytesPerLine());
            arg.convertTo(var,CV_8UC1);
            
            if (varIsThis==false) {
                QImage::operator=(std::move(_tmp));
            }
            return *this;
        }
        else if (varChannels==3) {
            /*分配内存*/
            QImage _tmp;
            if ((this->format()==QImage::Format_RGB888)&&
                (this->height()==arg.rows)&&
                (this->width()==arg.cols)&&
                (this->data_ptr()->own_data)) {
                this->detach();
                _tmp=*this;
                varIsThis=true;
            }
            else { 
                _tmp=QImage{ arg.cols,arg.rows,QImage::Format_RGB888 };
            }
            /*设置包装*/
            cv::Mat var(_tmp.height(),_tmp.width(),
                CV_8UC3,
                const_cast<uchar *>(_tmp.constBits()),
                _tmp.bytesPerLine());
            arg.convertTo(var,CV_8UC3);

            if (varIsThis==false) {
                QImage::operator=(std::move(_tmp));
            }
            return *this;
        }
        else if (varChannels==4) {
            /*分配内存*/
            QImage _tmp;
            if ((this->format()==QImage::Format_RGBA8888)&&
                (this->height()==arg.rows)&&
                (this->width()==arg.cols)&&
                (this->data_ptr()->own_data)) {
                this->detach();
                _tmp=*this;
                varIsThis=true;
            }
            else { 
                _tmp=QImage{ arg.cols,arg.rows,QImage::Format_RGBA8888 };
            }
            /*设置包装*/
            cv::Mat var(_tmp.height(),_tmp.width(),
                CV_8UC4,
                const_cast<uchar *>(_tmp.constBits()),
                _tmp.bytesPerLine());
            arg.convertTo(var,CV_8UC4);

            if (varIsThis==false) {
                QImage::operator=(std::move(_tmp));
            }
            return *this;
        }
    } while (false);
    QImage::operator=(QImage{});
    return *this;
}

/*创建opencv数据,进行深拷贝*/
cv::Mat QOpencvImage::toOpencvMat() const {
    QOpencvImage tmp(*this);
    cv::Mat ans=tmp._p_toOpencvRef();
    return ans.clone();
}

cv::Mat QOpencvImage::toOpencvRef() {
    if (this->data_ptr()->own_data==false) {
        QImage::operator=(this->copy())/*获得独立拷贝*/;
    }
    else {
        this->detach()/*获得独立拷贝*/;
    }
    return _p_toOpencvRef();
}






