#ifndef __SHADOW_THREAD__HPP_0x998126_PRIVATE
#define __SHADOW_THREAD__HPP_0x998126_PRIVATE

#include <thread>
#include <functional>
#include <type_traits>
#include "../../config/config.hpp"
#include "../../cplusplus_basic.hpp"

namespace thread {

class _CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT ShadowThread final {
public:
    typedef void(*TypePlainFunction)();
    typedef void(*TypePlainVoidStarFunction)(void *);
    typedef void(*TypePlainConstVoidStarFunction)(const void *);
    typedef std::function<void(void)> TypeStdFunction;
    ShadowThread();
    ~ShadowThread();
    void quit();
    static ShadowThread * instance();
public:
    std::thread::id getThreadID()const;

    template<typename T,
        typename=std::enable_if_t<true==std::is_convertible<T&&,TypePlainFunction>::value>
    >void run(T && arg) { _p_run_plain_function(arg); }

    template<typename T,
        typename=std::enable_if_t<false==std::is_convertible<T&&,TypePlainFunction>::value>,
        typename=void*
    >void run(T && arg) { _p_run_std_function(std::move(arg)); }

    void run(TypePlainVoidStarFunction a,void *b) { _p_run_plain_voidstar_function(a,b); }
    void run(TypePlainConstVoidStarFunction a,const void *b) { 
        _p_run_plain_constvoidstar_function(a,b); }
private:
    class _PrivateShadowThread;
    char __m_thisp[sizeof(std::shared_ptr<_PrivateShadowThread>)];
    std::shared_ptr<_PrivateShadowThread> & thisp();
    std::shared_ptr<const _PrivateShadowThread> & thisp()const;
    void _p_run_plain_function(TypePlainFunction);
    void _p_run_std_function(TypeStdFunction);
    void _p_run_plain_voidstar_function(TypePlainVoidStarFunction,void *);
    void _p_run_plain_constvoidstar_function(TypePlainConstVoidStarFunction,const void *);
public:
    ShadowThread(const ShadowThread&)=delete;
    ShadowThread&operator=(const ShadowThread&)=delete;
    ShadowThread(ShadowThread&&)=delete;
    ShadowThread&operator=(ShadowThread&&)=delete;
private:
    CPLUSPLUS_OBJECT(ShadowThread)
};
 
template<typename T>
inline void runInShadowThread(T && arg) {
    ShadowThread::instance()->run(std::move(arg));
}

inline void runInShadowThread(ShadowThread::TypePlainVoidStarFunction a,void *b) {
    ShadowThread::instance()->run(a,b);
}

inline void runInShadowThread(ShadowThread::TypePlainConstVoidStarFunction a,const void *b) { 
    ShadowThread::instance()->run(a,b); 
}

}/*thread*/

#endif
