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
    testRSAPublicKeyEncode();
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

void MainWindow::testRSAPublicKeyEncode() {
    using Botan::byte;
    using Botan::Public_Key;
    using Botan::PK_Encryptor_EME;
    constexpr byte pemData[]=u8R"///(-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDoUaLxcCvcgWzS1ukXC56F9YWx
PlmuwHa9zPFR4+tinzhtG8PRSgPB7UOAzaFu4hKimPOcOrQaRUof/PhSNGxZAhad
d+/kot0I8y7pwzeza9EAEwpQIki7RextKlWDRLRvaQGLjnW7SUrF2k62zJCdtow0
KcfR+Hx1+7Z4wYYFHwIDAQAB
-----END PUBLIC KEY-----
)///";
    Botan::MemoryVector<byte> pem(pemData,sizeof(pemData)-1);
    std::unique_ptr<Public_Key> publicKey{ Botan::X509::load_key(pem) };
    Botan::AutoSeeded_RNG rng;
    PK_Encryptor_EME en(*publicKey,"EME-PKCS1-v1_5");
    auto ans=en.encrypt((const byte*)"12345",5,rng);
    std::cout<<"encode rsa is : ";
    for (const auto varI:ans) {
        std::cout<<std::hex<<int(varI);
    }
    std::cout<<std::endl;
}

