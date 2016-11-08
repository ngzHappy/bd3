#ifndef _EXCEPTION_HPP_0x325678
#define _EXCEPTION_HPP_0x325678

#include "../memory/Memory.hpp"
#include <exception>
#include <stdexcept>

namespace exception {

class ExceptionHandle {
    ExceptionHandle&operator=(const ExceptionHandle&)=delete;
    ExceptionHandle&operator=(ExceptionHandle&&)=delete;
    ExceptionHandle(const ExceptionHandle&)=delete;
    ExceptionHandle(ExceptionHandle&&)=delete;
public:
    virtual ~ExceptionHandle()=default;
    virtual void print_exception(bool argExit=true) noexcept(true)=0;
    virtual void print_information(const char*,std::size_t) noexcept(true)=0;
    virtual void print_error(const char*,std::size_t) noexcept(true)=0;
    ExceptionHandle()=default;
public:
    inline void print_information(const char *arg,int argl) {
        print_information(arg,static_cast<std::size_t>(argl));
    }
    inline void print_error(const char *arg,int argl) {
        print_error(arg,static_cast<std::size_t>(argl));
    }
};

typedef std::unique_ptr<ExceptionHandle>(*CreateExceptionHandleFunction)(int/*line*/,const char * /*func*/,const char * /*file*/);
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT CreateExceptionHandleFunction getCreateExceptionHandleFunction();
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT CreateExceptionHandleFunction setCreateExceptionHandleFunction(CreateExceptionHandleFunction);

}/*exception*/

namespace exception {

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void exception_handle(
    bool a_exit=true,
    int a_line=0,
    const char * a_functionName=nullptr,
    const char * a_fileName=nullptr) noexcept(true);

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void information_handle(
    const char * a_info,int a_len,
    int a_line=0,
    const char * a_functionName=nullptr,
    const char * a_fileName=nullptr) noexcept(true);

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void error_handle(
    const char * a_error,int a_len,
    int a_line=0,
    const char * a_functionName=nullptr,
    const char * a_fileName=nullptr) noexcept(true);

}/*exception*/

#endif


