#ifndef ABSTRACTIMAGESHIFT_HPP
#define ABSTRACTIMAGESHIFT_HPP

#include <QtGui/qimage.h>
#include "OpenCVBasic.hpp"

class AbstractImageShift {
public:
    AbstractImageShift()=default;
    virtual ~AbstractImageShift()=default;
public:
    virtual QImage run(const QImage&) const=0;
private:
    CPLUSPLUS_OBJECT(AbstractImageShift)
};

#endif // ABSTRACTIMAGESHIFT_HPP
