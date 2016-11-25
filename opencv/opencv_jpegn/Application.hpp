/*Application.hpp*/
#ifndef APPLICATION_HPP_0x12998
#define APPLICATION_HPP_0x12998

#include <cplusplus_basic.hpp>
#include <ImageShowUtility.hpp>

class Application final: public OpencvApplication
{
    Q_OBJECT

private:
    using _Super=OpencvApplication;
    class _PrivateApplication;
    _PrivateApplication * _thisp=nullptr;
public:
    Application(int,char **);
    ~Application();

public:
    Application(const Application &)=delete;
    Application(Application &&)=delete;
    Application&operator=(const Application &)=delete;
    Application&operator=(Application &&)=delete;
private:
    CPLUSPLUS_OBJECT(Application)
};

#endif // APPLICATION_HPP


/*End of the file.*/

