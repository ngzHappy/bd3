#include "Application.hpp"

class Application::_PrivateApplication{
public:

private:
    CPLUSPLUS_OBJECT(_PrivateApplication)
};

Application::Application(int argc, char ** argv)
    :_Super(THIS_PROJECT_BUILD_DIR,THIS_PROJECT_BUILD_DIR,
            argc,argv){
    _thisp=new _PrivateApplication;
}

Application::~Application(){
    delete _thisp;
}

/*End of the file.*/

