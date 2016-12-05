#include <utility>
#include <type_traits>

namespace utiliy{

template<typename L>
const auto & rget(const std::reference_wrapper<L> &l) { return l.get(); }
template<typename L>
const auto & rget(const std::reference_wrapper<L> &&l) { return l.get(); }
template<typename L>
auto & rget(std::reference_wrapper<L> &l) { return l.get(); }
template<typename L>
auto && rget(std::reference_wrapper<L> &&l) { return std::move(l.get()); }
template<typename L>
const auto & rget(const L &l) { return l; }
template<typename L>
const auto & rget(const L &&l) { return l; }
template<typename L>
auto & rget(L &l) { return l; }
template<typename L>
auto && rget(L &&l) { return std::move(l); }

template<typename L,typename R>
bool operator<(const std::reference_wrapper<L>&l,const std::reference_wrapper<R>&r) {
    return l.get()<r.get();
}

template<typename L,typename R>
bool operator<=(const std::reference_wrapper<L>&l,const std::reference_wrapper<R>&r) {
    return l.get()<=r.get();
}

template<typename L,typename R>
bool operator>(const std::reference_wrapper<L>&l,const std::reference_wrapper<R>&r) {
    return l.get()>r.get();
}

template<typename L,typename R>
bool operator>=(const std::reference_wrapper<L>&l,const std::reference_wrapper<R>&r) {
    return l.get()>=r.get();
}

template<typename L,typename R>
bool operator==(const std::reference_wrapper<L>&l,const std::reference_wrapper<R>&r) {
    return l.get()==r.get();
}

template<typename L,typename R>
bool operator!=(const std::reference_wrapper<L>&l,const std::reference_wrapper<R>&r) {
    return l.get()!=r.get();
}

////////////////////////////////////

template<typename L,typename R>
bool operator<(const std::reference_wrapper<L>&l,const R&r) {
    return l.get()<r;
}

template<typename L,typename R>
bool operator<=(const std::reference_wrapper<L>&l,const R&r) {
    return l.get()<=r;
}

template<typename L,typename R>
bool operator>(const std::reference_wrapper<L>&l,const R&r) {
    return l.get()>r;
}

template<typename L,typename R>
bool operator>=(const std::reference_wrapper<L>&l,const R&r) {
    return l.get()>=r;
}

template<typename L,typename R>
bool operator==(const std::reference_wrapper<L>&l,const R&r) {
    return l.get()==r;
}

template<typename L,typename R>
bool operator!=(const std::reference_wrapper<L>&l,const R&r) {
    return l.get()!=r;
}

////////////////////////////////////

template<typename L,typename R>
bool operator<(const L&l,const std::reference_wrapper<R>&r) {
    return l<r.get();
}

template<typename L,typename R>
bool operator<=(const L&l,const std::reference_wrapper<R>&r) {
    return l<=r.get();
}

template<typename L,typename R>
bool operator>(const L&l,const std::reference_wrapper<R>&r) {
    return l>r.get();
}

template<typename L,typename R>
bool operator>=(const L&l,const std::reference_wrapper<R>&r) {
    return l>=r.get();
}

template<typename L,typename R>
bool operator==(const L&l,const std::reference_wrapper<R>&r) {
    return l==r.get();
}

template<typename L,typename R>
bool operator!=(const L&l,const std::reference_wrapper<R>&r) {
    return l!=r.get();
}

/**********************************************************************/
template<typename L,typename R>
auto operator+(const L&l,const std::reference_wrapper<R>&r) {
    return l+r.get();
}





}/*utility*/

