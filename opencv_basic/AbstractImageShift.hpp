#ifndef ABSTRACTIMAGESHIFT_HPP
#define ABSTRACTIMAGESHIFT_HPP

class QPainter;
#include <QtGui/qimage.h>
#include "OpenCVBasic.hpp"

class AbstractImageShift {
public:
    AbstractImageShift()=default;
    virtual ~AbstractImageShift()=default;
public:
    virtual QImage run(const QImage&) const=0;
    virtual void paint(QPainter *,const QSize &/*image size*/){
        /*gui系统先调用run,再调用paint*/}
private:
    CPLUSPLUS_OBJECT(AbstractImageShift)
};

#endif // ABSTRACTIMAGESHIFT_HPP



