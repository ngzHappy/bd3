#include <stack>
#include "deque.hpp"
#include "../cplusplus_basic.hpp"

namespace containers {

template <typename T,
          typename C = containers::deque<T> >
using stack=std::stack<T,C>;

}/*containers*/
