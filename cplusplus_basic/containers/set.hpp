#include <set>
#include "../cplusplus_basic.hpp"

namespace containers {

template<typename T,typename C=std::less<void>>
using set=std::set<T,C,memory::Allocator<T>>;

template<typename T,typename C=std::less<void>>
using multiset=std::multiset<T,C,memory::Allocator<T>>;

}/*containers*/

