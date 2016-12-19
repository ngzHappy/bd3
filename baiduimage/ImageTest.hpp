#ifndef IMAGETEST_HPP
#define IMAGETEST_HPP

#include "BaiduUser.hpp"
#include <QtWidgets/QWidget>

namespace Ui {
class ImageTest;
}

class ImageTest : public QWidget{
    Q_OBJECT

public:
    explicit ImageTest(QWidget *parent = 0);
    ~ImageTest();

private slots:
    void on_nextStep_clicked();
private:
    baidu::BaiduUser * baiduUser=nullptr;
private:
    Ui::ImageTest *ui;
};

#endif // IMAGETEST_HPP





