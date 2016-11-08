#ifndef _MEMORY_HPP_0x877160
#define _MEMORY_HPP_0x877160

#include "../config/config.hpp"

namespace memory {

_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void clean();
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void * malloc(int arg);
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT void free(void * arg);
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT int size(void * arg);
_CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT int cookie_size();
inline void free(const void *arg) { memory::free(const_cast<void*>(arg)); }
inline int size(const void *arg) { return memory::size(const_cast<void*>(arg)); }
inline void freePoolMemory() { memory::clean(); }

}/*memory*/

#endif


