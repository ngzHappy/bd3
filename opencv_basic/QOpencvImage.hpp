#ifndef QOPENCVIMAGE_HPP_0x000001
#define QOPENCVIMAGE_HPP_0x000001

#include "OpenCVBasic.hpp"
#include <QtGui/qimage.h>
#include <opencv2/opencv.hpp>

class OPENCV3_BASICHARED_EXPORT QOpencvImage : public QImage
{
    using _Super=QImage;
public:
    using _Super::_Super;
    ~QOpencvImage();
    QOpencvImage();
    QOpencvImage(const QOpencvImage&);
    QOpencvImage(QOpencvImage&&);
    QOpencvImage(const QImage&);
    QOpencvImage(QImage&&);
protected:
    const QImage & _p_getImage()const &{return *this;}
    QImage && _p_getImage()&&{return std::move(*this);}
    QImage & _p_getImage()&{return *this;}
private:
    CPLUSPLUS_OBJECT(QOpencvImage)
};

#endif // QOPENCVIMAGE_HPP
