#ifndef __CPLUSPLUS_BASIC_HPP_0X97721
#define __CPLUSPLUS_BASIC_HPP_0X97721

#include <utility>
#include <numeric>
#include <algorithm>
#include "memory/Memory.hpp"
#include "utility/type_traits.hpp"
#include "exception/Exception.hpp"

#ifndef CPLUSPLUS_OBJECT
#define CPLUSPLUS_OBJECT(_objname_) inline static constexpr auto __0x21_size() noexcept(true){ return sizeof(_objname_); } MEMORY_CLASS_NEW_DELETE
#endif

#ifndef CPLUSPLUS_EXCEPTION
#define CPLUSPLUS_EXCEPTION(_is_quit_) exception::exception_handle(static_cast<bool>(_is_quit_),__LINE__,__func__,__FILE__)
#endif // !CPLUSPLUS_EXCEPTION

#endif

