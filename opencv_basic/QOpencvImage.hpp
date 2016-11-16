#ifndef QOPENCVIMAGE_HPP_0x000001
#define QOPENCVIMAGE_HPP_0x000001

#include "OpenCVBasic.hpp"
#include <QtGui/qimage.h>
#include <opencv2/opencv.hpp>

class OPENCV3_BASICHARED_EXPORT QOpencvImage : public QImage {
    using _Super=QImage;
public:
    using _Super::_Super;
    ~QOpencvImage();
    QOpencvImage();
    QOpencvImage(const QOpencvImage&);
    QOpencvImage(QOpencvImage&&);
    QOpencvImage(const QImage&);
    QOpencvImage(QImage&&);

    QOpencvImage&operator=(const QOpencvImage&)=default;
    QOpencvImage&operator=(QOpencvImage&&)=default;

    /*
    创建opencv数据,
    进行浅拷贝,
    可能会早成QImage格式变换,
    不要令此数据脱离函数栈区
    */
    cv::Mat toOpencvRef();
    /*创建opencv数据,进行深拷贝*/
    cv::Mat toOpencvMat()const;
    /*进行深拷贝*/
    QOpencvImage & fromOpencvMat(const cv::Mat &);

protected:
    const QImage & _p_getImage()const & { return *this; }
    QImage && _p_getImage()&&{return std::move(*this); }
    QImage & _p_getImage()& { return *this; }
    cv::Mat _p_toOpencvRef();
private:
    CPLUSPLUS_OBJECT(QOpencvImage)
};

#endif // QOPENCVIMAGE_HPP
