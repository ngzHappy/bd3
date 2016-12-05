#ifndef __SHADOW_THREAD__HPP_0x998126_PRIVATE
#define __SHADOW_THREAD__HPP_0x998126_PRIVATE

#include "../../config/config.hpp"
#include "../../cplusplus_basic.hpp"

namespace thread {

class _CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT ShadowThread final{
public:
    ShadowThread();
    ~ShadowThread();

    static ShadowThread * instance();
public:
    ShadowThread(const ShadowThread&)=delete;
    ShadowThread&operator=(const ShadowThread&)=delete;
    ShadowThread(ShadowThread&&)=delete;
    ShadowThread&operator=(ShadowThread&&)=delete;
private:
    CPLUSPLUS_OBJECT(ShadowThread)
};

}/*thread*/

#endif
