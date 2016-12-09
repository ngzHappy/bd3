#include "TestException.hpp"
#include <botan/botan.h>
#include <iostream>
TestException::TestException() try {

    try {
        throw_runtime_error("test",4);
    }
    catch (...) {
        exception::exception_handle(false);
    }
    
    Botan::LibraryInitializer botan;
    Botan::BigInt test(2132);
    test+=999999; test*=222222;
    test+=999999; test*=222222;
    test+=999999; test*=222222;
    test+=999999; test*=222222;
    test+=999999; test*=222222;
    test+=999999; test*=222222;
    test+=999999; test*=222222;
    test+=999999; test*=222222;
    test+=999999; test*=222222;
    test+=999999; test*=222222;

    Botan::BigInt test1=test;
    test*=test1;
    test*=test1;
    test*=test1;
    test*=test1;
    test*=test1;
    test*=test1;

    auto text = Botan::BigInt::encode(test,Botan::BigInt::Decimal);
    std::cout<<"big num : ";
    for (const auto i:text) {
        std::cout<<i ;
    }
    std::cout<<std::endl;

}
catch (...) {
    exception::exception_handle(false);
}
