#ifndef OPENCVBASIC_HPP_0x99821
#define OPENCVBASIC_HPP_0x99821

#include <QtCore/qglobal.h>
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>
#include <cplusplus_basic.hpp>

#if defined(OPENCV3_BASIC_LIBRARY)
#  define OPENCV3_BASICHARED_EXPORT Q_DECL_EXPORT
#else
#  define OPENCV3_BASICHARED_EXPORT Q_DECL_IMPORT
#endif

class OPENCV3_BASICHARED_EXPORT OpenCVBasic
{
public:
    OpenCVBasic();
    virtual ~OpenCVBasic();
};

#endif // OPENCVBASIC_HPP
