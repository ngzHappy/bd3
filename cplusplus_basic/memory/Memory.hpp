﻿#ifndef _MEMORY_HPP_0x877160
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

#if !defined(MEMORY_CLASS_NEW_DELETE)

#if defined(__cplusplus)
#define MEMORY_CLASS_NEW_DELETE public: \
static void operator delete(void *arg) { memory::free(arg); } \
static void operator delete[](void *arg) { memory::free(arg); } \
static void * operator new(std::size_t n) { auto ans=memory::malloc(static_cast<int>(n)); if (ans) { return ans; }throw std::bad_alloc{}; } \
static void * operator new[](std::size_t n) { auto ans=memory::malloc(static_cast<int>(n)); if (ans) { return ans; }throw std::bad_alloc{}; }
#else
#define MEMORY_CLASS_NEW_DELETE
#endif/*MEMORY_CLASS_NEW_DELETE*/

#endif
 
namespace memory {

class _CPLUSPLUS_BASIC_LIBRARYSHARED_EXPORT __memory__construct_static {
    friend void constructStatic();
protected:
    static bool __is_construct_static() noexcept(true);
    static void __set_construct_static() noexcept(true);
    static bool __run_once(void(*)(void)) noexcept(true);
};

}/*namespace memory*/

/*****************************************/
#include "private/Allocator.hpp"
#include "private/MakeShared.hpp"
#include "private/MakeFunction.hpp"
#include "private/MemoryStatic.hpp"
#include "private/MemoryApplication.hpp"
/*****************************************/

#endif


