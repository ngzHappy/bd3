#include <string>
#include "LoginTest.hpp"
#include "ui_LoginTest.h"
#include <QtCore/qdebug.h>

LoginTest::LoginTest(QWidget *parent):
    QWidget(parent),
    ui(new Ui::LoginTest) {
    ui->setupUi(this);
    test_uncompress_baiduimage_url();
    /***********************************/
    vertifyitem=new QGraphicsPixmapItem;
    ui->imageShow->setScene( new QGraphicsScene( ui->imageShow ) );
    ui->imageShow->scene()->addItem(vertifyitem);
    baiduUser=new baidu::BaiduUser(memory::make_shared<QSingleThreadPool>());
    /***********************************/
    connect(baiduUser,&baidu::BaiduUser::loginFinished,
            this,[this](bool a,const QString & b,const QImage & c) {
        if (a) {
            qDebug()<<"log in finished";
            return;
        }
        qDebug()<<"log in fail"<<b;
        if (c.isNull()==false) {
            vertifyitem->setPixmap(QPixmap::fromImage(c));
        }
    });
}

LoginTest::~LoginTest() {
    delete ui;
    delete baiduUser;
}

void LoginTest::on_login_clicked() {

    if (baiduUser==nullptr) {
        baiduUser=new baidu::BaiduUser(memory::make_shared<QSingleThreadPool>());
    }

    baiduUser->login(
                ui->userName->text(),
                ui->passWord->text(),
                ui->vertifyCode->text()
                );

}

void LoginTest::test_uncompress_baiduimage_url(){
    using namespace baidu;
    BaiduUser::uncompressBaiduImageUrl(nullptr,nullptr);
    using namespace std::string_literals;

    {
        auto test="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"s;
        auto ans_range=BaiduUser::uncompressBaiduImageUrl((char*)test.c_str(),test.c_str()+test.size());
        std::string ans(ans_range.first,ans_range.second);
        qDebug()<<ans.c_str();
    }

    {
        auto test="_z2C$q"s;
        auto ans_range=BaiduUser::uncompressBaiduImageUrl((char*)test.c_str(),test.c_str()+test.size());
        std::string ans(ans_range.first,ans_range.second);
        qDebug()<<ans.c_str();
    }

    {
        auto test="_z&e3BAAA"s;
        auto ans_range=BaiduUser::uncompressBaiduImageUrl((char*)test.c_str(),test.c_str()+test.size());
        std::string ans(ans_range.first,ans_range.second);
        qDebug()<<ans.c_str();
    }

    {
        auto test="AzdH3FAAA"s;
        auto ans_range=BaiduUser::uncompressBaiduImageUrl((char*)test.c_str(),test.c_str()+test.size());
        std::string ans(ans_range.first,ans_range.second);
        qDebug()<<ans.c_str();
    }

}

void LoginTest::on_deleteButton_clicked(){
    if(baiduUser){
        delete baiduUser;
        baiduUser=nullptr;
    }
}

void LoginTest::on_imageButton_clicked(){

    if (baiduUser==nullptr) {
        baiduUser=new baidu::BaiduUser(memory::make_shared<QSingleThreadPool>());
    }

    auto imageTest = memory::make_shared<baidu::BaiduImage>();
    imageTest->setKeyWord(QString::fromUtf8(u8R"///(美女)///"));
    baiduUser->downLoad( imageTest );

}
