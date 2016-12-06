#ifndef ABSTRACTIMAGESHIFT_HPP
#define ABSTRACTIMAGESHIFT_HPP

class QPainter;
#include <vector>
#include <QtGui/qimage.h>
#include "OpenCVBasic.hpp"

class AbstractGetImage {
public:
    virtual ~AbstractGetImage()=default;
    virtual const QImage & getImage() const=0;
};

class AbstractDrawFunction {
public:
    virtual ~AbstractDrawFunction()=default;
    virtual void paint(QPainter *,const QSizeF &/*image size or axis size*/)=0;
};

class AbstractImageShift :public AbstractDrawFunction {
public:
    using ImageVector=std::vector<const QImage*,memory::Allocator<QImage*>/**/>;
    AbstractImageShift()=default;
    virtual ~AbstractImageShift()=default;
public:
    virtual QImage run(const QImage &/*the first image*/)=0;
    virtual void paint(QPainter *,const QSizeF &/*image size or axis size*/) override {
        /*gui系统先调用run,再调用paint*/
    }
private:
};

#endif // ABSTRACTIMAGESHIFT_HPP



