#include <forward_list>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T>
using forward_list=std::forward_list<T,memory::Allocator<T>>;

}/*containers*/

