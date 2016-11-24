#include <type_traits>

template<typename _T_>
class AddSafeConst {
public:
    typedef const _T_ type;
};

template<typename _T_>
class AddSafeConst<_T_&> {
    static_assert(std::is_reference<_T_>::value==false,
        "_T_ should not be a reference");
public:
    typedef typename AddSafeConst<_T_>::type & type;
};

template<typename _T_>
class AddSafeConst<_T_&&> {
    static_assert(std::is_reference<_T_>::value==false,
        "_T_ should not be a reference");
public:
    typedef typename AddSafeConst<_T_>::type && type;
};

template<typename _T_>
class AddSafeConst<_T_*> {
public:
    typedef typename AddSafeConst<_T_>::type * const type;
};
