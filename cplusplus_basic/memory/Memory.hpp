#ifndef _MEMORY_HPP_0x877160
#define _MEMORY_HPP_0x877160

#include "../config/config.hpp"

namespace memory {

CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void clean();
CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void * malloc(int arg);
CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void free(void * arg);
CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT int size(void * arg);
CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT int cookie_size();
inline void free(const void *arg) { memory::free(const_cast<void*>(arg)); }
inline void freePoolMemory() { memory::clean(); }

}/*memory*/

#endif


