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

#endif


