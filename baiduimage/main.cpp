#include "MainWindow.hpp"
#include <cplusplus_basic.hpp>
#include <QtBasicLibrary.hpp>
#include <QtWidgets/QApplication>

#include "BaiduUser.hpp"

int main(int argc, char *argv[])try{

    /*init memory*/
    memory::Application mapp;
    /*init qt basic library*/
    QtBasicLibrary qtBasicLibrary;

    QApplicationWatcher<QApplication> app(argc, argv);

    MainWindow window;
    window.show();

    baidu::BaiduUser user( memory::make_shared<QSingleThreadPool>() );
    user.login("abc","def");

    {
        auto ans = app->exec();
        mapp.quit();
        return ans;
    }

}catch(...){
    CPLUSPLUS_EXCEPTION(true);
    return -1;
}


