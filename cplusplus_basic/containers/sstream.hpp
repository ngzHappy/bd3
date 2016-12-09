#ifndef _sstream_HASH_CONTAINERS_HPP_0x1222
#define _sstream_HASH_CONTAINERS_HPP_0x1222

#include <sstream>
#include "../cplusplus_basic.hpp"

namespace containers {

using stringstream = std::basic_stringstream<char,std::char_traits<char>,memory::Allocator<char>>;
using wstringstream = std::basic_stringstream<wchar_t,std::char_traits<wchar_t>,memory::Allocator<wchar_t>>;

}/*containers*/

#endif
