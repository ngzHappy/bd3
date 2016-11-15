#ifndef OPENCVBASIC_HPP_0x99821
#define OPENCVBASIC_HPP_0x99821

/*basic*/
#include <QtCore/qglobal.h>
#include <QtCore/qstring.h>
#include <cplusplus_basic.hpp>
#include <QtCore/qbytearray.h>
/*opencv*/
#include <opencv2/opencv.hpp>

#if defined(OPENCV3_BASIC_LIBRARY)
#  define OPENCV3_BASICHARED_EXPORT Q_DECL_EXPORT
#else
#  define OPENCV3_BASICHARED_EXPORT Q_DECL_IMPORT
#endif

class OPENCV3_BASICHARED_EXPORT OpenCVBasic {
public:
    OpenCVBasic();
    virtual ~OpenCVBasic();
private:
    CPLUSPLUS_OBJECT(OpenCVBasic)
};

#endif // OPENCVBASIC_HPP
