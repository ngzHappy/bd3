#include <QtCore>
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->projectName->setPlaceholderText(
                QString::fromUtf8(u8"项目名称"));
}

MainWindow::~MainWindow() {
    delete ui;
}

namespace {
inline QString operator""_qu8(const char *a,std::size_t n) {
    return QString::fromUtf8(a,static_cast<int>(n));
}
}/**/

static inline bool write_file_with_bom(
    const QString & fileName,
    const QString & fileData
) {
    QFile file(fileName);
    if (false==file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    textStream<<bom;

    textStream<<fileData;

    return true;
}

void MainWindow::on_doButton_clicked() {

    const QString project_rpath="/../../";
    const QString project_path=THIS_PROJECT_DIR;
    const QString project_name=ui->projectName->text().trimmed();

    QString pro_file_data;
    const QString proFileName=project_path+project_rpath+"opencv3.pro";

    {/*显示opencv3.pro*/
        QFile file(proFileName);
        if (file.open(QIODevice::ReadOnly)==false) {
            ui->textShow->setText("can not find:"+proFileName);
            return;
        }
        QTextStream textStream(&file);
        pro_file_data=textStream.readAll().trimmed();
        ui->textShow->setText(pro_file_data);
    }

    QString dir_project;
    {/*创建目录*/
        QDir dir;
        dir_project=project_path+project_rpath+"opencv/"+project_name;
        dir.mkpath(dir_project);
    }

    {/*创建Application.hpp*/
        auto varFileName=dir_project+"/Application.cpp";
        auto varFileData=u8R"_!_(/*Application.cpp*/
#include "Application.hpp"

class Application::_PrivateApplication{
public:

private:
    CPLUSPLUS_OBJECT(_PrivateApplication)
};

Application::Application(int argc, char ** argv)
    :_Super(THIS_PROJECT_BUILD_DIR,THIS_PROJECT_BUILD_DIR,
            argc,argv){
    _thisp=new _PrivateApplication;
}

Application::~Application(){
    delete _thisp;
}

#include <memory/MemoryApplication.hpp>

/*End of the file.*/

)_!_"_qu8;
        write_file_with_bom(varFileName,varFileData);
    }

    {
        auto varFileName=dir_project+"/"+
            project_name+".lua";
        auto varFileData=u8R"_!_(--[[lua--]]
local application={
input_images={
"images:000001",
"images:000002",
"images:000003",
},--[[input_images--]]
input_data_2d={
{0.01*10,0.53213436611265*10},
}--[[input_data_2d--]]

}

return application

--[[lua--]]
)_!_";
        write_file_with_bom(varFileName,varFileData);
    }

    {/*创建Application.hpp*/
        auto varFileName=dir_project+"/Application.hpp";
        auto varFileData=u8R"_!_(/*Application.hpp*/
#ifndef APPLICATION_HPP_0x12998
#define APPLICATION_HPP_0x12998

#include <cplusplus_basic.hpp>
#include <ImageShowUtility.hpp>

class Application final: public OpencvApplication
{
    Q_OBJECT

private:
    using _Super=OpencvApplication;
    class _PrivateApplication;
    _PrivateApplication * _thisp=nullptr;
public:
    Application(int,char **);
    ~Application();

public:
    Application(const Application &)=delete;
    Application(Application &&)=delete;
    Application&operator=(const Application &)=delete;
    Application&operator=(Application &&)=delete;
private:
    CPLUSPLUS_OBJECT(Application)
};

#endif // APPLICATION_HPP


/*End of the file.*/

)_!_"_qu8;
        write_file_with_bom(varFileName,varFileData);
    }

    {/*创建MainWindow.hpp*/
        auto varFileName=dir_project+"/MainWindow.hpp";
        auto varFileData=u8R"_!_(#ifndef MAINWINDOW_HPP_0x12778
#define MAINWINDOW_HPP_0x12778

#include <cplusplus_basic.hpp>
#include <ImageShowUtility.hpp>

class MainWindow final : public OpencvMainWindow {
    Q_OBJECT

private:
    using _Super=OpencvMainWindow;
    class _PrivateMainWindow;
    _PrivateMainWindow * _thisp=nullptr;
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

    using _Super::addImage;
    QWidget* addImage(const QImage &) override;
    void openLua() override;

public:
    MainWindow(const MainWindow&)=delete;
    MainWindow(MainWindow&&)=delete;
    MainWindow&operator=(const MainWindow&)=delete;
    MainWindow&operator=(MainWindow&&)=delete;
private:
    CPLUSPLUS_OBJECT(MainWindow)
};

#endif // MAINWINDOW_HPP

/*End of the file.*/

)_!_"_qu8;
        write_file_with_bom(varFileName,varFileData);
    }

    {/*创建MainWindow.cpp*/
        auto varFileName=dir_project+"/MainWindow.cpp";
        auto varFileData=u8R"_!_(/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>

class MainWindow::_PrivateMainWindow{
public:
private:
    CPLUSPLUS_OBJECT(_PrivateMainWindow)
};

MainWindow::MainWindow(QWidget *parent) :
    _Super(parent){
    _thisp=new _PrivateMainWindow;
}

MainWindow::~MainWindow(){
     delete _thisp;
}

/*write your code here*/
QWidget* MainWindow::addImage(const QImage &arg) {
    return _Super::addImage(arg);
}

void MainWindow::openLua(){
    return _Super::openLua();
}

/*End of the file.*/

)_!_"_qu8;
        write_file_with_bom(varFileName,varFileData);
    }

    {/*创建main.cpp*/
        auto varFileName=dir_project+"/main.cpp";
        auto varFileData=u8R"_!_(/*main.cpp*/
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
    QApplicationWatcher<Application> * _v_application=nullptr;
    QTimer * _v_gctimer=nullptr;
public:
    inline MainState(int,char **);
    inline int exec();
    inline ~MainState();

    Application * app() const { return _v_application->get(); }
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
    _v_application=new QApplicationWatcher<Application>(argc,argv);
    /*init gctimer*/
    _v_gctimer=new QTimer;
    _v_gctimer->connect(_v_gctimer,&QTimer::timeout,[]() {memory::clean(); });
    _v_gctimer->start(512);
}

/*执行*/
inline int MainState::exec() {
    return app()->exec();
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

int main(int argc,char *argv[])try {

    auto varMainState=
        std::make_unique<MainState>(argc,argv);

    MainWindow varMainWindow;
    /*注入启动数据*/
    varMainWindow.openLua();
    varMainWindow.show();

    return varMainState->exec();

}
catch (...) {
    CPLUSPLUS_EXCEPTION(true);
    return -1;
}

/*End of the file.*/

)_!_"_qu8;
        write_file_with_bom(varFileName,varFileData);
    }

    /*****************************************/
    {
        QFile file(dir_project+"/"+project_name+".pro");
        if (false==file.open(QIODevice::WriteOnly)) {
            return;
        }
        QTextStream textStream(&file);
        auto write_data=u8R"_!_(###$$$.pro

QT += core
QT += gui
QT += widgets
#QT += script
#QT += network

TARGET = $$$
TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    Application.cpp

HEADERS  += MainWindow.hpp \
    Application.hpp

FORMS    +=

RESOURCES +=

DISTFILES += \
    $$PWD/$$$.lua

DEFINES *= THIS_PROJECT_BUILD_DIR=\\\"$$PWD\\\"

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

include($$PWD/../../opencv_basic/opencv_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lopencv3_basic_library

)_!_"_qu8;;
        textStream<<write_data.replace("$$$"_qu8,project_name);

    }

    {
        //pro_file_data
        auto writeData=u8R"_!_(

$$$.file=$$PWD/opencv/$$$/$$$.pro
$$$.depends+=library_opencv_basic
SUBDIRS += $$$

)_!_"_qu8;
        writeData.replace("$$$"_qu8,project_name);

        pro_file_data+=std::move(writeData);

        QFile file(proFileName);
        if (false==file.open(QIODevice::WriteOnly)) {
            return;
        }
        QTextStream textStream(&file);
        textStream<<pro_file_data;
        ui->textShow->setText(pro_file_data);
    }

}

