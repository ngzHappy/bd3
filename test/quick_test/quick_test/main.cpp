#include "MainWindow.hpp"
#include <QtWidgets/QApplication>
#include "TestMemory.hpp"
#include "TestException.hpp"
#include "TestLua.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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
