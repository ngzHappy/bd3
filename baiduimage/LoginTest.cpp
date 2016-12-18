#include "LoginTest.hpp"
#include "ui_LoginTest.h"

LoginTest::LoginTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginTest){
    ui->setupUi(this);
}

LoginTest::~LoginTest(){
    delete ui;
}

