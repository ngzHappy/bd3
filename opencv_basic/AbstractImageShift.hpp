#ifndef ABSTRACTIMAGESHIFT_HPP
#define ABSTRACTIMAGESHIFT_HPP

class QPainter;
#include <QtGui/qimage.h>
#include "OpenCVBasic.hpp"

class AbstractDrawFunction{
public:
    virtual ~AbstractDrawFunction()=default;
    virtual void paint(QPainter *,const QSizeF &/*image size or axis size*/)=0;
};

class AbstractImageShift :public AbstractDrawFunction{
public:
    AbstractImageShift()=default;
    virtual ~AbstractImageShift()=default;
public:
    virtual QImage run(const QImage&) const=0;
    virtual void paint(QPainter *,const QSizeF &/*image size or axis size*/) override{
        /*gui系统先调用run,再调用paint*/}
private:
};

#endif // ABSTRACTIMAGESHIFT_HPP



