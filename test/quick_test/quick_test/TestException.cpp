#include "TestException.hpp"

TestException::TestException(){

    try {
        throw std::logic_error("test");
    }
    catch (...) {
        exception::exception_handle(false);
    }



}
