#ifndef __HASH_CONTAINERS_HPP_0x1222
#define __HASH_CONTAINERS_HPP_0x1222

#include <utility>
#include <functional>
#include <type_traits>

namespace containers {

namespace /*ⓟ*/\u24df{

template<typename ...>using _void_t=void;

template<typename T,typename U,typename=void>
class IsStdHash :public std::false_type {};

template<typename T,typename U>
class IsStdHash<T,U,_void_t<
        decltype( std::declval<std::hash<T>>()(std::declval<U>()) )
>>:public std::true_type{};

}/**/

template<typename T,typename=void>
class MixHash{
public:
    //std::hash<T>
//    template<typename U,
//             typename K=std::enable_if_t<
//                 u24df::IsStdHash<T,const U&>::value>>
//    size_t operator()(const U &arg){
//        std::hash<T> var;
//        return var(arg);
//    }
};

template<typename T>
class MixHash<T,\u24df::_void_t<
        std::enable_if_t<sizeof(std::hash<T>)>
>>{
  std::hash<T> _p_std_hash;
public:
      template<typename U,
               typename K=std::enable_if_t<
                   u24df::IsStdHash<T,const U&>::value>>
      size_t operator()(const U &arg) const {
          return _p_std_hash(arg);
      }
};

}/*containers*/

#endif


