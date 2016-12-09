#include <exception>
#include <stdexcept>
#include "botan.h"

Botan::Exception::Exception():
    _Super("std::runtime_error") {
}

Botan::Exception::Exception(const containers::string &arg) :
    _Super(""){
    _pm_data=memory::make_shared<containers::string>(arg);
}

Botan::Exception::Exception(containers::string &&arg) :
    _Super(""){
    _pm_data=memory::make_shared<containers::string>(std::move(arg));
}

const char * Botan::Exception::what() const {
    if (_pm_data) { return reinterpret_cast< 
        containers::string *>( _pm_data.get() )->c_str(); }
    return _Super::what();
}

Botan::Invalid_Argument::Invalid_Argument() :
    _Super("Invalid_Argument"){
}

Botan::Invalid_Argument::Invalid_Argument(const containers::string &arg):
    _Super("") {
    _pm_data=memory::make_shared<containers::string>(arg);
}

Botan::Invalid_Argument::Invalid_Argument(containers::string &&arg):
    _Super("") {
    _pm_data=memory::make_shared<containers::string>(std::move(arg));
}

const char * Botan::Invalid_Argument::what() const {
    if (_pm_data) { return reinterpret_cast< 
        containers::string *>( _pm_data.get() )->c_str(); }
    return _Super::what();
}
