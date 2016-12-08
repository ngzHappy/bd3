#include <deque>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T>
using deque=std::deque<T,memory::Allocator<T>>;

}/*containers*/



