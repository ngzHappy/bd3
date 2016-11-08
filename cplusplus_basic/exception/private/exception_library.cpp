#include "../Exception.hpp"
#include <mutex>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <shared_mutex>

namespace exception {

namespace {
inline namespace _exception_private {

/************************************************************************/
inline void _p_exit() { return std::exit(-1); }
inline void _p_quick_exit() { return std::exit(-2); }

using _string_t=std::basic_string<char,std::char_traits<char>,memory::Allocator<char>>;
inline _string_t operator""_s(const char *arg,std::size_t argl) {
    return _string_t(arg,argl);
}

class _ExceptionHandle final :public exception::ExceptionHandle {
    typedef std::recursive_mutex _mutex_t;
    typedef std::unique_lock<_mutex_t> _lock_t;
    using _sstream_t=std::basic_stringstream<char,std::char_traits<char>,memory::Allocator<char>>;
    static char _psm_mutex[sizeof(_mutex_t)];
    static _mutex_t & _p_mutex() {
        /*never delete*/
        static auto var=::new (_psm_mutex) _mutex_t;
        return *var;
    }
    bool _pm_exit_=true;
    int _pm_line;
    const char *_pm_functionname;
    const char *_pm_filename;
    template<typename _T_,int _N_>
    static void _p_write(_T_&argO,const char(&arg)[_N_]) {
        argO.write(arg,(_N_-1));
    }
    template<typename _T_,typename _U_>
    static void _p_write(_T_&argO,_U_&&argD) {
        argO<<std::forward<_U_>(argD);
    }
    void __p_write(_sstream_t&arg) {
        _lock_t _{ _p_mutex() };
        std::cout<<arg.rdbuf();
    }
protected:
    template<int _N_>
    void lprint_error(const char(&arg)[_N_]) {
        print_error(arg,(_N_-1));
    }
    template<int _N_>
    void lprint_information(const char(&arg)[_N_]) {
        print_information(arg,(_N_-1));
    }
public:

    _ExceptionHandle(
                int argLine,
                const char *argFunc,
                const char *argFile
    ):_pm_line(argLine),_pm_functionname(argFunc),_pm_filename(argFile) {
    }

    void bad_exception_handle() noexcept(true) {
        try {
            lprint_error("bad_exception_handle");
        }
        catch (...) {}
        _p_quick_exit();
    }

    void std_exception_handle(const std::exception &e) noexcept(true) {

        try {
            _string_t var="std::exception "_s+e.what();
            print_information(var.data(),var.size());
        }
        catch (...) {
            bad_exception_handle();
        }

        try {
            std::rethrow_if_nested(e);
        }
        catch (...) {
            print_exception(_pm_exit_);
        }

    }

    void std_logic_error_handle(const std::logic_error &e) noexcept(true) {

        try {
            _string_t var="std::logic_error "_s+e.what();
            if (_pm_exit_) {
                print_error(var.data(),var.size());
            }
            else {
                print_information(var.data(),var.size());
            }
        }
        catch (...) {
            bad_exception_handle();
        }

        try {
            std::rethrow_if_nested(e);
        }
        catch (...) {
            print_exception(_pm_exit_);
        }

    }

    virtual void print_exception(bool argExit) noexcept(true) override {
        _pm_exit_=argExit;
        try {
            std::rethrow_exception(std::current_exception());
        }
        catch (const std::bad_alloc&) {
            print_error("bad_alloc",9);
        }
        catch (const std::logic_error&e) {
            std_logic_error_handle(e);
        }
        catch (const std::exception &e) {
            std_exception_handle(e);
        }
        catch (...) {

            try {
                if (argExit) {
                    lprint_error("unknow exception ");
                }
                else {
                    lprint_information("unknow exception ");
                }
            }
            catch (...) {
                bad_exception_handle();
            }

        }
    }

    virtual void print_information(const char* arg,std::size_t argl) noexcept(true) override {
        if (arg&&(argl>0)) {
            try {
                _sstream_t varStream;
                _p_write(varStream,"information : ");
                if (_pm_filename&&_pm_functionname) {
                    _p_write(varStream,"@line : ");
                    _p_write(varStream,_pm_line);
                    _p_write(varStream," @function_name : ");
                    _p_write(varStream,_pm_functionname);
                    _p_write(varStream," @file_name : ");
                    _p_write(varStream,_pm_filename);
                }
                _p_write(varStream,"\n");
                varStream.write(arg,argl);
                _p_write(varStream,"\n");
                __p_write(varStream);
            }
            catch (...) {/*?????*/
                _p_quick_exit();
            }
        }
    }

    virtual void print_error(const char* arg,std::size_t argl) noexcept(true) override {
        if (arg&&(argl>0)) {
            try {
                _sstream_t varStream;
                _p_write(varStream,"error : ");
                if (_pm_filename&&_pm_functionname) {
                    _p_write(varStream,"@line : ");
                    _p_write(varStream,_pm_line);
                    _p_write(varStream," @function_name : ");
                    _p_write(varStream,_pm_functionname);
                    _p_write(varStream," @file_name : ");
                    _p_write(varStream,_pm_filename);
                }
                _p_write(varStream,"\n");
                varStream.write(arg,argl);
                _p_write(varStream,"\n");
                __p_write(varStream);
            }
            catch (...) {}
        }
        _p_quick_exit();
    }

};

char _ExceptionHandle::_psm_mutex[sizeof(_ExceptionHandle::_mutex_t)];
/************************************************************************/

class __CreateExceptionHandleFunction {
    typedef std::shared_timed_mutex _mutex_t;
    typedef std::shared_lock<_mutex_t> _slock_t;
    typedef std::unique_lock<_mutex_t> _ulock_t;
    CreateExceptionHandleFunction _pm_function;
    _mutex_t _pm_mutex;
public:
    __CreateExceptionHandleFunction():_pm_function(
                                          [](int a1,const char *a2,const char *a3)->std::unique_ptr<ExceptionHandle> {
        try {
            ExceptionHandle *var=new _ExceptionHandle{ a1,a2,a3 };
            return std::unique_ptr<ExceptionHandle>{var};
        }
        catch (...) {/*?????*/
            _p_quick_exit();
        }
        return nullptr;
    }
    ) {
    }
    CreateExceptionHandleFunction get() {
        _slock_t _{ _pm_mutex };
        return _pm_function;
    }
    CreateExceptionHandleFunction set(CreateExceptionHandleFunction arg) {
        _ulock_t _{ _pm_mutex };
        auto varOld=_pm_function;
        _pm_function=arg;
        return varOld;
    }
};

char _sd_CreateExceptionHandleFunction[sizeof(__CreateExceptionHandleFunction)];
inline __CreateExceptionHandleFunction *get_CreateExceptionHandleFunction() {
    /*never delete*/
    static auto var=::new (_sd_CreateExceptionHandleFunction) __CreateExceptionHandleFunction;
    return var;
}

}/*_private*/
}/*namespace*/


CreateExceptionHandleFunction getCreateExceptionHandleFunction() {
    return get_CreateExceptionHandleFunction()->get();
}

CreateExceptionHandleFunction setCreateExceptionHandleFunction(
        CreateExceptionHandleFunction arg) {
    if (arg==nullptr) { return getCreateExceptionHandleFunction(); }
    return get_CreateExceptionHandleFunction()->set(arg);
}

void exception_handle(
    bool a_exit,
    int a_line,
    const char * a_functionName,
    const char * a_fileName) noexcept(true) {

    try {
        auto var=getCreateExceptionHandleFunction()(a_line,a_functionName,a_fileName);
        var->print_exception(a_exit);
    }
    catch (...) {
        _p_quick_exit();
    }

}

void information_handle(
    const char * a_info,int a_len,
    int a_line,
    const char * a_functionName,
    const char * a_fileName) noexcept(true) {
    try {
        auto var=getCreateExceptionHandleFunction()(a_line,a_functionName,a_fileName);
        var->print_information(a_info,a_len);
    }
    catch (...) {
        _p_quick_exit();
    }
}

void error_handle(
    const char * a_error,int a_len,
    int a_line,
    const char * a_functionName,
    const char * a_fileName) noexcept(true) {
    try {
        auto var=getCreateExceptionHandleFunction()(a_line,a_functionName,a_fileName);
        var->print_error(a_error,a_len);
    }
    catch (...) {
        _p_quick_exit();
    }
}

}/*exception*/



