#include "TestException.hpp"

TestException::TestException(){

    try {
        throw std::logic_error("test");
    }
    catch (...) {
        auto ehandle= exception::getCreateExceptionHandleFunction()(
            __LINE__,__func__,__FILE__);
        ehandle->print_exception(false);
    }

}
