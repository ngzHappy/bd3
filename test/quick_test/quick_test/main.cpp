#include "MainWindow.hpp"
#include <QtWidgets/QApplication>
#include "TestMemory.hpp"
#include "TestException.hpp"
#include "TestLua.hpp"
#include <QtCore/qtimer.h>
#include <QtCore/qdebug.h>
#include <text/gzip.hpp>
#include <thread/ShadowThread.hpp>

int main(int argc, char *argv[])try
{

    std::set_new_handler( memory::get_memory_not_enough() );
    {
        const char * v="123";
        text::gzip(v,v+3);
    }

    memory::Application memory_app;
    QApplication app(argc, argv);

    /*每隔一段时间清理内存*/
    QTimer gcTimer;
    gcTimer.connect(&gcTimer,&QTimer::timeout,
                    [](){memory::clean();});
    gcTimer.start(512);


    {/*测试内存*/
        TestMemory test;
    }

    {/*测试异常*/
        TestException test;
    }

    {/*测试lua*/
        TestLua test;
    }

    {
        int a=12;
        thread::ShadowThread::instance()->run([]() {
            qDebug()<<"test ShadowThread";
        });

        thread::ShadowThread::instance()->run([a]() {
            qDebug()<<"test ShadowThread"<<a;
        });

        thread::ShadowThread::instance()->run([](void *a) {
            qDebug()<<"test ShadowThread"<<a;
        },&a);

        thread::ShadowThread::instance()->run([](const void *a) {
            qDebug()<<"test ShadowThread const"<<a;
        },&a);

    }

    MainWindow window;
    window.show();

    auto app_ans= app.exec();
    memory_app.quit();
    return app_ans;

    thread::ShadowThread::instance()->quit();
}
catch (...) {
    exception::exception_handle(true,
        __LINE__,__func__,__FILE__);
    return -7;
}
