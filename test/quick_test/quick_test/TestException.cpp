#include "TestException.hpp"

TestException::TestException(){

    try {
        throw_runtime_error("test",4);
    }
    catch (...) {
        exception::exception_handle(false);
    }
    
  

}
