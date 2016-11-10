#include "MainWindow.hpp"
#include <QtWidgets/QApplication>
#include "TestMemory.hpp"
#include "TestException.hpp"
#include "TestLua.hpp"
#include <QtCore/qtimer.h>
#include <text/gzip.hpp>

int main(int argc, char *argv[])try
{

    {
        const char * v="123";
        text::gzip(v,v+3);
    }

    memory::Application memory_app;
    QApplication app(argc, argv);

    /*每隔一段时间清理内存*/
    //QTimer gcTimer;
    //gcTimer.connect(&gcTimer,&QTimer::timeout,
    //                [](){memory::clean();});
    //gcTimer.start(512);


    {/*测试内存*/
        TestMemory test;
    }

    {/*测试异常*/
        TestException test;
    }

    {/*测试lua*/
        TestLua test;
    }

    MainWindow window;
    window.show();

    auto app_ans= app.exec();
    memory_app.quit();
    return app_ans;
}
catch (...) {
    exception::exception_handle(true,
        __LINE__,__func__,__FILE__);
    return -7;
}
