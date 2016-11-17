#include <QtCore>
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->projectName->setPlaceholderText(
                QString::fromUtf8(u8"项目名称"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

namespace {
inline QString operator""_qu8(const char *a,std::size_t n) {
    return QString::fromUtf8(a,static_cast<int>(n));
}
}/**/

void MainWindow::on_doButton_clicked(){

    const QString project_rpath="/../../";
    const QString project_path=THIS_PROJECT_DIR;
    const QString project_name=ui->projectName->text().trimmed();

    QString pro_file_data;
    const QString proFileName=project_path+project_rpath+"opencv3.pro";
    {
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
    {
        QDir dir;
        dir_project=project_path+project_rpath+"opencv/"+project_name;
        dir.mkpath(dir_project);
    }

    {
        QFile file(dir_project+"/main.cpp");
        if (false==file.open(QIODevice::WriteOnly)) {
            return;
        }
        QTextStream textStream(&file);
        textStream.setCodec("UTF-8");
        textStream<<bom;
        textStream<<u8R"_!_(/*main.cpp*/

#include "MainWindow.hpp"
#include <QtCore/qtimer.h>
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>
#include <QtWidgets/QApplication>

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

)_!_"_qu8;
    }     

/*****************************************/
    {
        QFile file(dir_project+"/"+project_name+".pro");
        if (false==file.open(QIODevice::WriteOnly)) {
            return;
        }
        QTextStream textStream(&file);
        auto write_data=u8R"_!_(###$$$.pro

###$$$.pro

QT += core
QT += gui
QT += widgets
#QT += script
#QT += network

TARGET = $$$
TEMPLATE = app

SOURCES += main.cpp

HEADERS  +=  

FORMS    +=  

DEFINES *= THIS_PROJECT_BUILD_DIR=\\\"$$PWD\\\"

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

include($$PWD/../../opencv_basic/opencv_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lopencv3_basic_library

RESOURCES += \
    source.qrc

DISTFILES += \
    $$PWD/$$$.lua


)_!_"_qu8;;
        textStream<<write_data.replace("$$$"_qu8,project_name);

    }

    {
        //pro_file_data
        auto writeData=u8R"_!_(

$$$.file=$$PWD/opencv/$$$/$$$.pro
$$$.depends+=library_cplusplus_basic
$$$.depends+=qt_basic_library
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
