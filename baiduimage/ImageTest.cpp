#include "ImageTest.hpp"
#include "ui_ImageTest.h"

ImageTest::ImageTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageTest){
    ui->setupUi(this);
}

ImageTest::~ImageTest(){
    delete ui;
}

void ImageTest::on_nextStep_clicked(){

    if(baiduUser==nullptr){
        baiduUser=new baidu::BaiduUser( memory::make_shared<QSingleThreadPool>() );
    }

    auto imageTest = memory::make_shared<baidu::BaiduImage>();
    imageTest->setKeyWord(QString::fromUtf8(u8R"///(美女)///"));
    baiduUser->downLoad( imageTest );

}


