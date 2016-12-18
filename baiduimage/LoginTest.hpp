#ifndef LOGINTEST_HPP
#define LOGINTEST_HPP

#include <QtWidgets/QWidget>

namespace Ui {
class LoginTest;
}

class LoginTest : public QWidget
{
    Q_OBJECT

public:
    explicit LoginTest(QWidget *parent = 0);
    ~LoginTest();

private:
    Ui::LoginTest *ui;
};

#endif // LOGINTEST_HPP
