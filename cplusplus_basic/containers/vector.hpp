#include <vector>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T>
using vector=std::vector<T,memory::Allocator<T>>;

}/*containers*/

