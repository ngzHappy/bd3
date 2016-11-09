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
    using size_t=std::size_t;
    using isize_t=std::make_signed_t<size_t>;
    virtual ~ExceptionHandle()=default;
    ExceptionHandle()=default;
protected:
    virtual void _do_print_exception(bool argExit) noexcept(true)=0;
    virtual void _do_print_information(const char*,size_t) noexcept(true)=0;
    virtual void _do_print_error(const char*,size_t) noexcept(true)=0;
    virtual void _do_quick_exit() noexcept(true)=0;
public:
    template<typename _C_T_>
    inline void print_information(const _C_T_ * const &arg,isize_t argl) noexcept(true){
        _do_print_information(arg,static_cast<size_t>(argl));
    }
    template<typename _C_T_>
    inline void print_information(const _C_T_ * const &arg,size_t argl) noexcept(true){
        _do_print_information(arg,argl);
    }
    template<typename _C_T_,int _N_>
    inline void print_information(_C_T_(&arg)[_N_]) {
        _do_print_information(arg,static_cast<size_t>(_N_-1));
    } 

    template<typename _C_T_>
    inline void print_error(const _C_T_ * const &arg,isize_t argl) noexcept(true){
        _do_print_error(arg,static_cast<size_t>(argl));
    }
    template<typename _C_T_>
    inline void print_error(const _C_T_ * const &arg,size_t argl) noexcept(true){
        _do_print_error(arg,argl);
    }
    template<typename _C_T_,int _N_>
    inline void print_error(_C_T_(&arg)[_N_]) {
        _do_print_error(arg,static_cast<size_t>(_N_-1));
    } 

    inline void print_exception(bool argExit=true) noexcept(true){
        _do_print_exception(argExit);
    }
    inline void quick_exit() noexcept(true){ _do_quick_exit(); }
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


