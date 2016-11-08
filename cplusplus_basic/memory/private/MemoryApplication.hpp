#ifndef _m_MEMORY_APPLICATION_1_
#define _m_MEMORY_APPLICATION_1_

#include "../Memory.hpp"

#ifndef IS_PLUGIN_FIRE
#define IS_PLUGIN_FIRE false
#endif

namespace memory {
class _CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT Application {
    static void _p_setMainConstruct();
    static void _p_clearMainConstruct();
    static void _p_setMainQuit();
    static void _p_clearMainQuit();
public:
    Application() { _p_setMainConstruct(); }
    ~Application() { _p_setMainQuit(); }

    static bool isMainConstruct();
    static bool isMainQuit();
};

}/*namespace memory*/

#endif

