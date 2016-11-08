﻿#include "MainWindow.hpp"
#include <QtWidgets/QApplication>
#include "TestMemory.hpp"
#include "TestException.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    {/*测试内存*/
        TestMemory test;
    }

    {/*测试异常*/
        TestException test;
    }

    MainWindow window;
    window.show();

    return app.exec();
}
