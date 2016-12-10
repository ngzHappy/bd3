/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::test() try {
    testMD5();
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

void MainWindow::test_assert(bool arg,const char * ans) {
    if (arg==false) {
        throw std::logic_error(ans);
    }
}

#include <iostream>
#include <botan/botan.h>
void MainWindow::testMD5() {
/*
https://botan.randombit.net/doxygen/
Hash Functions
Blake2b, GOST 34.11, Keccak,
MD4, MD5, RIPEMD-160,
SHA-1, SHA-224, SHA-256,
SHA-384, SHA-512, Skein-512,
Tiger, Whirlpool
*/
    using Botan::byte;
    using Botan::HashFunction;
    {
        std::unique_ptr<HashFunction> md5Hash{ Botan::get_hash("MD5") };

        auto ans=md5Hash->process((const byte *)"12345",5);
        std::cout<<"md5 for 12345 : ";
        for (const auto varI:ans) {
            std::cout<<std::hex<<int(varI);
        }
        std::cout<<std::endl;

        constexpr byte right_ans[]={ 0x82,0x7c,0xcb,0x0e,0xea,0x8a,0x70,0x6c,
            0x4c,0x34,0xa1,0x68,0x91,0xf8,0x4e,0x7b };

        test_assert(ans.size()==16,"md5 size error");
        test_assert(Botan::same_mem(right_ans,ans.begin(),16),"md5 is not right");
    }
    {
        using Botan::MD5;
        MD5 md5;
        auto ans=md5.process((const byte *)"12345",5);
        std::cout<<"md5 for 12345 : ";
        for (const auto varI:ans) {
            std::cout<<std::hex<<int(varI);
        }
        std::cout<<std::endl;

        constexpr byte right_ans[]={ 0x82,0x7c,0xcb,0x0e,0xea,0x8a,0x70,0x6c,
            0x4c,0x34,0xa1,0x68,0x91,0xf8,0x4e,0x7b };

        test_assert(ans.size()==16,"md5 size error");
        test_assert(Botan::same_mem(right_ans,ans.begin(),16),"md5 is not right");
    }
}



