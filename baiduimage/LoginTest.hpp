#ifndef LOGINTEST_HPP
#define LOGINTEST_HPP

#include "BaiduUser.hpp"
#include <QtWidgets/QWidget>
#include <QtWidgets/qgraphicsitem.h>

namespace Ui {
class LoginTest;
}

class LoginTest : public QWidget{
    Q_OBJECT

public:
    explicit LoginTest(QWidget *parent = 0);
    ~LoginTest();
private:
    void test_uncompress_baiduimage_url();
private slots:
    void on_login_clicked();
    void on_deleteButton_clicked();
    void on_imageButton_clicked();

private:
    QGraphicsPixmapItem * vertifyitem;
    baidu::BaiduUser * baiduUser;
private:
    Ui::LoginTest *ui;
};

#endif // LOGINTEST_HPP
