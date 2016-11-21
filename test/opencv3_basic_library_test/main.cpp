/*main.cpp*/
#include "MainWindow.hpp"
#include <QtCore/qtimer.h>
#include <QtCore/qtextcodec.h>
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>
#include "Application.hpp"
#include "MainWindow.hpp"

namespace {

class MainState {
    memory::Application * _v_memory_application=nullptr;
    QtBasicLibrary * _v_qtbasiclibrary=nullptr;
    Application * _v_application=nullptr;
    QTimer * _v_gctimer=nullptr;
public:
    inline MainState(int,char **);
    inline int exec();
    inline ~MainState();

    Application * app() const { return _v_application; }
public:
    MainState(const MainState&)=delete;
    MainState(MainState&&)=delete;
    MainState&operator=(const MainState&)=delete;
    MainState&operator=(MainState&&)=delete;
private:
    CPLUSPLUS_OBJECT(MainState)
};

/*构造应用程序*/
inline MainState::MainState(int argc,char **argv) {
    /*init new handler*/
    std::set_new_handler([]() { memory::get_memory_not_enough()(); });
#if defined(LOCAL_CODEC_OF_THE_PROJECT)
    /*set local codec*/
    QTextCodec::setCodecForLocale(
        QTextCodec::codecForName(LOCAL_CODEC_OF_THE_PROJECT));
#endif
    /*init memory application*/
    _v_memory_application=new memory::Application;
    /*init qt basic library*/
    _v_qtbasiclibrary=new QtBasicLibrary;
    /*init opencv application*/
    _v_application=new Application(argc,argv);
    /*init gctimer*/
    _v_gctimer=new QTimer;
    _v_gctimer->connect(_v_gctimer,&QTimer::timeout,[]() {memory::clean(); });
    _v_gctimer->start(512);
}

/*执行*/
inline int MainState::exec() {
    return _v_application->exec();
}

/*重定义析构顺序*/
inline MainState::~MainState() {
    _v_memory_application->quit();
    delete _v_gctimer;
    delete _v_memory_application;
    delete _v_qtbasiclibrary;
    delete _v_application;
}

}/*namespace*/

#include <vector>

class TestDrawCallBack :public AbstractImageShift {
public:
    QImage run(const QImage&arg) const override {
        try {
            QOpencvImage var(arg);
            cv::Mat refMat=var.toOpencvRef();
            cv::flip(refMat,refMat,-1);
            return var;
        }
        catch (...) {
            CPLUSPLUS_EXCEPTION(true);
        }
        return arg;
    }

    virtual void paint(
        QPainter * painter,
        const QSizeF & size) override {
        painter->setBrush(QColor(0,0,0,0));
        painter->setPen(QPen(QColor(0,0,0),3));
        painter->drawRect(QRect(QPoint(0,0),size.toSize()));
    }
private:
    CPLUSPLUS_OBJECT(TestDrawCallBack)
};

int main(int argc,char *argv[])try {

    auto varMainState=
        std::make_unique<MainState>(argc,argv);

    MainWindow varMainWindow;

    varMainWindow.addImage(varMainState->app()->getAllImageNames());

    {
        auto var=new ImageShowWidget;
        var->setImage(QImage(":/0x000000.jpg"));
        var->setAlgorithm(memory::make_shared<TestDrawCallBack>());

        {
            auto cv=new DataChartView;
            auto c=cv->dataChart();
            addScatterSeries(c,
                std::vector<QPointF>{QPointF(0,0),
                    QPointF(100,100),
            });
            var->addImageWidget(cv);
        }

        {
            auto cv=new DataChartView;
            auto c=cv->dataChart();
            addLineSeries(c,
                std::vector<QPointF>{QPointF(0,0),
                    QPointF(100,100),
            });
            var->addImageWidget(cv,Qt::DockWidgetArea::RightDockWidgetArea);
        }

        varMainWindow.addWidget(var)
            ->setWindowTitle("abcd");
    }


    varMainWindow.show();

    return varMainState->exec();

}
catch (...) {
    CPLUSPLUS_EXCEPTION(true);
    return -1;
}

/*End of the file.*/
