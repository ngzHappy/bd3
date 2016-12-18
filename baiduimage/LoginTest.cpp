#include "LoginTest.hpp"
#include "ui_LoginTest.h"
#include <QtCore/qdebug.h>

LoginTest::LoginTest(QWidget *parent):
    QWidget(parent),
    ui(new Ui::LoginTest) {
    ui->setupUi(this);
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
        vertifyitem->setPixmap( QPixmap::fromImage(c) );
    });
}

LoginTest::~LoginTest() {
    delete ui;
}

void LoginTest::on_login_clicked() {
    baiduUser->login(
    ui->userName->text(),
    ui->passWord->text(),
    ui->vertifyCode->text()
    );
}







