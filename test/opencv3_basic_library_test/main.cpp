/*main.cpp*/

#include "MainWindow.hpp"
#include <QtCore/qtimer.h>
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>
#include <QtWidgets/QApplication>
#include <ImageShowWidget.hpp>
#include <PlainImageView.hpp>
#include <ImageChart.hpp>
#include <ImageChartView.hpp>

int main(int argc, char *argv[])try{
    /*init new handler*/
    std::set_new_handler( memory::get_memory_not_enough() );
    /*init memory application*/
    memory::Application mapp;
    /*init qt basic library*/
    QtBasicLibrary qtBasicLibrary;

    QApplication app(argc, argv);

    /*每隔一段时间清理内存*/
    QTimer gcTimer;
    gcTimer.connect(&gcTimer,&QTimer::timeout,
                    [](){memory::clean();});
    gcTimer.start(512);

    //MainWindow window;
    //window.show();

    ImageShowWidget widget;
    widget.setChartImage(QImage(":/0x000000.jpg"))
        ->setAlgorithm([](const QImage &arg)->QImage {
        return arg.mirrored(true,true);
    });

    widget.show();

    {
        auto ans = app.exec();
        mapp.quit();
        return ans;
    }

}catch(...){
    CPLUSPLUS_EXCEPTION(true);
    return -1;
}


