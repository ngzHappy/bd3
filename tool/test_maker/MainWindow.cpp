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
    const QString proFileName=project_path+project_rpath+"baidu3.pro";
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
        dir_project=project_path+project_rpath+"test/"+project_name;
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

    QApplicationWatcher<QApplication> app(argc, argv);

    /*每隔一段时间清理内存*/
    QTimer gcTimer;
    gcTimer.connect(&gcTimer,&QTimer::timeout,
                    [](){memory::clean();});
    gcTimer.start(512);

    MainWindow window;
    window.show();

    {
        auto ans = app->exec();
        mapp.quit();
        return ans;
    }

}catch(...){
    CPLUSPLUS_EXCEPTION(true);
    return -1;
}

)_!_"_qu8;
    }

    {
        QFile file(dir_project+"/MainWindow.hpp");
        if (false==file.open(QIODevice::WriteOnly)) {
            return;
        }
        QTextStream textStream(&file);
        textStream.setCodec("UTF-8");
        textStream<<bom;
        textStream<<u8R"_!_(/*MainWindow.hpp*/
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <cplusplus_basic.hpp>
#include <QtWidgets/QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private:
    CPLUSPLUS_OBJECT(MainWindow)
};

#endif // MAINWINDOW_HPP

)_!_"_qu8;
    }

    {
        QFile file(dir_project+"/MainWindow.ui");
        if (false==file.open(QIODevice::WriteOnly)) {
            return;
        }
        QTextStream textStream(&file);
        textStream<<u8R"_!_(<ui version="4.0">
 <class>MainWindow</class>
 <widget class="QMainWindow" name="MainWindow" >
  <property name="geometry" >
   <rect>
    <x>0</x>
    <y>0</y>
    <width>400</width>
    <height>300</height>
   </rect>
  </property>
  <property name="windowTitle" >
   <string>MainWindow</string>
  </property>
  <widget class="QMenuBar" name="menuBar" />
  <widget class="QToolBar" name="mainToolBar" />
  <widget class="QWidget" name="centralWidget" />
  <widget class="QStatusBar" name="statusBar" />
 </widget>
 <layoutDefault spacing="6" margin="11" />
 <pixmapfunction></pixmapfunction>
 <resources/>
 <connections/>
</ui>

)_!_"_qu8;
    }

    {
        QFile file(dir_project+"/MainWindow.cpp");
        if (false==file.open(QIODevice::WriteOnly)) {
            return;
        }
        QTextStream textStream(&file);
        textStream.setCodec("UTF-8");
        textStream<<bom;
        textStream<<u8R"_!_(/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

)_!_"_qu8;
    }


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
#QT += charts
#QT += script
#QT += network

TARGET = $$$
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.hpp

FORMS    += MainWindow.ui

include($$PWD/../../this_project.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_basic/cplusplus_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lcplusplus_basic_library

include($$PWD/../../qt_basic/qt_basic.pri)
LIBS+=-L$$THIS_PROJECT_DESTDIR -lqt_basic_library

)_!_"_qu8;;
        textStream<<write_data.replace("$$$"_qu8,project_name);

    }

    {
        //pro_file_data
        auto writeData=u8R"_!_(

$$$.file=$$PWD/test/$$$/$$$.pro
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
