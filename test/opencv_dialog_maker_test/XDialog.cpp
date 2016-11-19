#include "XDialog.hpp"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtoolbutton.h>
#include <QtWidgets/qlayoutitem.h>

namespace  {

class _0x21Q_Label :public QLabel {
    using _Super=QLabel;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_Label)
};

class _0x21Q_ToolButton :public QToolButton {
    using _Super=QToolButton;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_ToolButton)
};

class _0x21Q_PushButton :public QPushButton {
    using _Super=QPushButton;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_PushButton)
};

class _0x21Q_SpacerItem :public QSpacerItem {
    using _Super=QSpacerItem;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_SpacerItem)
};

class _0x21Q_LineEdit :public QLineEdit {
    using _Super=QLineEdit;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_LineEdit)
};

class _0x21Q_HBoxLayout :public QHBoxLayout {
    using _Super=QHBoxLayout;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_HBoxLayout)
};

class _0x21Q_VBoxLayout :public QVBoxLayout {
    using _Super=QVBoxLayout;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_VBoxLayout)
};

}/*namespace*/

class XDialog::_PrivateXDialog{
public:
    XDialog *super;
    _PrivateXDialog(XDialog *arg):super(arg){}

    /*values*/

    constexpr static int default__x_Dialogtest0_0x2i(){return 22;}
    constexpr static int default_step__x_Dialogtest0_0x2i(){return 1;}
    constexpr static int max__x_Dialogtest0_0x2i(){return 30;}
    constexpr static int min__x_Dialogtest0_0x2i(){return 10;}
    int _x_Dialogtest0_0x2i=default__x_Dialogtest0_0x2i();
    int old__x_Dialogtest0_0x2i=default__x_Dialogtest0_0x2i();
    _0x21Q_LineEdit * edit__x_Dialogtest0_0x2i=nullptr;
    _0x21Q_LineEdit * edit_step__x_Dialogtest0_0x2i=nullptr;
    constexpr static double default__x_Dialogtest1_0x2d(){return 22.1;}
    constexpr static double default_step__x_Dialogtest1_0x2d(){return 0.1;}
    constexpr static double max__x_Dialogtest1_0x2d(){return 30.3;}
    constexpr static double min__x_Dialogtest1_0x2d(){return 10.2;}
    double _x_Dialogtest1_0x2d=default__x_Dialogtest1_0x2d();
    double old__x_Dialogtest1_0x2d=default__x_Dialogtest1_0x2d();
    _0x21Q_LineEdit * edit__x_Dialogtest1_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step__x_Dialogtest1_0x2d=nullptr;

    void setup_ui(){
        using namespace memory ;
        {

        }
    }

private:
    CPLUSPLUS_OBJECT(_PrivateXDialog)
};

XDialog::XDialog(QWidget *p):_Super(p){
    thisp=new _PrivateXDialog(this);
}

XDialog::~XDialog(){
    delete thisp;
}


