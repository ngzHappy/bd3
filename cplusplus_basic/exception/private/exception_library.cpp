#include "../Exception.hpp"
#include <mutex>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <shared_mutex>

namespace exception {

namespace {
inline namespace _exception_private {

inline void _p_exit() { return std::exit(-1); }
inline void _p_quick_exit() { return std::exit(-2); }

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
public:

    _ExceptionHandle(
        int argLine,
        const char *argFunc,
        const char *argFile
    ):_pm_line(argLine),
        _pm_functionname(argFunc),
        _pm_filename(argFile) {
    }

    virtual void print_exception(bool argExit) noexcept(true) override {
        try {
            std::rethrow_exception(std::current_exception());
        }
        catch (const std::bad_alloc&) {
            print_error("bad_alloc",9);
        }
        catch (const std::exception &) {

        }
        catch (...) {}
    }

    virtual void print_information(const char* arg,std::size_t argl) noexcept(true) override {
        if (arg&&(argl>0)) {
            try {
                _sstream_t varStream;
                _p_write(varStream,"information : ");
                if (_pm_filename&&_pm_functionname) {
                    _p_write(varStream,"@line : ");
                    _p_write(varStream,_pm_line);
                    _p_write(varStream,"@function_name : ");
                    _p_write(varStream,_pm_functionname);
                    _p_write(varStream,"@file_name : ");
                    _p_write(varStream,_pm_filename);
                }
                _p_write(varStream,"\n");
                varStream.write(arg,argl);
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
                    _p_write(varStream,"@function_name : ");
                    _p_write(varStream,_pm_functionname);
                    _p_write(varStream,"@file_name : ");
                    _p_write(varStream,_pm_filename);
                }
                _p_write(varStream,"\n");
                varStream.write(arg,argl);
                __p_write(varStream);
            }
            catch (...) {}
        }
        _p_quick_exit();
    }
};

char _ExceptionHandle::_psm_mutex[sizeof(_ExceptionHandle::_mutex_t)];

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

}/*exception*/



