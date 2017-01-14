/*
 * 此文件只能在一个项目中被编译一次
*/

#include <cplusplus_basic.hpp>

/*0*/
void * operator new(std::size_t arg){
    return memory::malloc(arg);
}

/*1*/
void operator delete(void * arg){
    return memory::free(arg);
}

/*2*/
void operator delete(void * arg,std::size_t){
    return memory::free(arg);
}

/*3*/
void * operator new[](std::size_t arg){
    return memory::malloc(arg);
}

/*4*/
void operator delete[](void * arg){
    return memory::free(arg);
}

/*5*/
void operator delete[](void * arg,std::size_t){
    return memory::free(arg);
}
