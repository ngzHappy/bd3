#include <list>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T>
using list=std::list<T,memory::Allocator<T>>;

}/*containers*/
