#ifndef OPENCVAPPLICATION_HPP
#define OPENCVAPPLICATION_HPP

#include "OpenCVBasic.hpp"
#include "QtWidgets/qapplication.h"
#include <string>

class OPENCV3_BASICHARED_EXPORT OpencvApplication :public QApplication {
    Q_OBJECT

public:
    using string_t=std::basic_string<char,std::char_traits<char>,
        memory::Allocator<char>/**/>;

    OpencvApplication(
            const QString&/*build path*/,
            const QString&/*image dir path*/,
            int/*argc*/,char ** /*argv*/);
    ~OpencvApplication();

    const QString & getBuildPath() const;
    const string_t & getLuaFileData() const;
public:
    OpencvApplication(const OpencvApplication&)=delete;
    OpencvApplication(OpencvApplication&&)=delete;
    OpencvApplication&operator=(const OpencvApplication&)=delete;
    OpencvApplication&operator=(OpencvApplication&&)=delete;

    static OpencvApplication * instance();
private:
    class _PrivateOpencvApplication;
    _PrivateOpencvApplication *_mp=nullptr;
    using _Super=QApplication;
private:
    CPLUSPLUS_OBJECT(OpencvApplication)
};

#undef qApp
#define qApp() OpencvApplication::instance()/**/

#endif // OPENCVAPPLICATION_HPP
