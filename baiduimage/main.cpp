#include "MainWindow.hpp"
#include <cplusplus_basic.hpp>
#include <QtBasicLibrary.hpp>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])try{

    /*init memory*/
    memory::Application mapp;
    /*init qt basic library*/
    QtBasicLibrary qtBasicLibrary;

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    {
        auto ans = app.exec();
        mapp.quit();
        return ans;
    }

}catch(...){
    CPLUSPLUS_EXCEPTION(true);
    return -1;
}


