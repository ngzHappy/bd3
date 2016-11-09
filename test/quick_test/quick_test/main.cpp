#include "MainWindow.hpp"
#include <QtWidgets/QApplication>
#include "TestMemory.hpp"
#include "TestException.hpp"
#include "TestLua.hpp"
#include <QtCore/qtimer.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*每隔一段时间清理内存*/
    QTimer gcTimer;
    gcTimer.connect(&gcTimer,&QTimer::timeout,
                    [](){memory::clean();});
    gcTimer.start(312);


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

    return app.exec();
}
