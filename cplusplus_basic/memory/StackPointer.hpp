#ifndef STACK_POINTER_HPP_0x79213
#define STACK_POINTER_HPP_0x79213

namespace memory {

template<typename _T_>
class StackPointer {
    _T_ * user_;
    _T_ * owner_;
public:
    constexpr StackPointer(_T_* arg):user_(arg),owner_(arg) {}
    constexpr StackPointer():StackPointer(nullptr) {}
    ~StackPointer() { delete owner_; }
    _T_* release() { owner_=nullptr; return user_; }
    _T_* release(_T_* arg) { auto ans=user_; owner_=arg;  user_=arg; return ans; }
    void reset(_T_* arg) { owner_=arg; user_=arg; }
    _T_* pointer() { return user_; }
    constexpr const _T_* pointer()const { return user_; }
    _T_* operator->() { return pointer(); }
    constexpr const _T_* operator->()const { return pointer(); }
    _T_& operator*() { return *pointer(); }
    constexpr const _T_& operator*()const { return *pointer(); }
    operator _T_* () { return pointer(); }
    constexpr operator const _T_* ()const { return pointer(); }
    constexpr explicit operator bool()const { return pointer()!=nullptr; }
    StackPointer& operator=(_T_* arg) { reset(arg); return *this; }
protected:
    StackPointer(StackPointer&&arg):user_(arg.user_),owner_(arg.owner_) {
        arg.owner_=nullptr;
    }
    StackPointer&operator=(StackPointer&&arg) {
        user_=arg.user_; owner_=arg.owner_; arg.owner_=nullptr;
    }
    StackPointer(const StackPointer&)=delete;
    StackPointer&operator=(const StackPointer&)=delete;
    template<typename _1T_,typename ..._1_Args>
    friend StackPointer<_1T_> makeStackPointer(_1_Args&&...);
};

template<typename _T_,typename ...Args>
StackPointer<_T_> makeStackPointer(Args&&...args) {
    /*rewrite in c++17*/
    return new _T_(std::forward<Args>(args)...);
}

}/*memory*/

#endif


