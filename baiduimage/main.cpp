#include "MainWindow.hpp"
#include <cplusplus_basic.hpp>
#include <QtBasicLibrary.hpp>
#include <QtWidgets/QApplication>

#include <QtCore/qtimer.h>

#include "BaiduUser.hpp"
#include "LoginTest.hpp"

#include <future>
#include <chrono>
#include <QtCore/qthread.h>
#include <QtNetwork/qnetworkaccessmanager.h>

class QNetWorkAccessManagerConstructThread :public QThread{
    std::promise<bool> * _return;
public:
    QNetWorkAccessManagerConstructThread(std::promise<bool> * arg):
        _return(arg) {
    }

    void run() override{
        QNetworkAccessManager var_manager;
        _return->set_value(true);
        exec();
    }
};


int main(int argc, char *argv[])try{

    /*init memory*/
    memory::Application mapp;
    /*init qt basic library*/
    QtBasicLibrary qtBasicLibrary;
      
    QApplicationWatcher<QApplication> app(argc, argv);

    /*每隔一段时间清理内存*/
    QTimer gcTimer;
    gcTimer.connect(&gcTimer,&QTimer::timeout,
        [](){memory::clean();});
    gcTimer.start(512);

    {
        std::promise<bool> promise;
        QNetWorkAccessManagerConstructThread networkThread(&promise);
        auto future = promise.get_future();
        networkThread.start();
        using namespace std::chrono_literals;
        if (future.wait_for(1s)==std::future_status::timeout) {
            networkThread.terminate();
            throw nullptr;
        }
        networkThread.quit();
        networkThread.wait(1000);
    }

    LoginTest test;
    test.show();

    {
        auto ans = app->exec();
        mapp.quit();
        return ans;
    }

}catch(...){
    CPLUSPLUS_EXCEPTION(true);
    return -1;
}

#include <memory/MemoryApplication.hpp>
