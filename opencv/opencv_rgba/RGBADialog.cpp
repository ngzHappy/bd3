#include "RGBADialog.hpp"
#include <QtWidgets/qlabel.h>
#include <QtGui/qvalidator.h>
#if defined(HAS_OPENCV_LIBRARY)
#include <opencv2/opencv.hpp>
#endif
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtoolbutton.h>
#include <QtWidgets/qlayoutitem.h>

namespace  {

class _0x21Q_ComboBox :public QComboBox {
    using _Super=QComboBox;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_ComboBox)
};

typedef void (QComboBox::*T_0x21Q_CurrentIndexChanged)(int);

constexpr int _0x21Q_decimals=6;

class Step_0x21Q_DoubleValidator :public QDoubleValidator {
    using _Super=QDoubleValidator;
public:
    Step_0x21Q_DoubleValidator(QObject * arg=nullptr):
        _Super(-9999,9999,_0x21Q_decimals,arg) {
        setNotation(QDoubleValidator::StandardNotation);
    }
    void setRange(double a,double b) {
        _Super::setRange(a,b,_0x21Q_decimals);
    }
private:
    CPLUSPLUS_OBJECT(Step_0x21Q_DoubleValidator)
};

class _0x21Q_DoubleValidator :public QDoubleValidator {
    using _Super=QDoubleValidator;
public:
    _0x21Q_DoubleValidator(QObject * arg=nullptr):
        _Super(-360,360,_0x21Q_decimals,arg){
        setNotation(QDoubleValidator::StandardNotation);
    }
    void setRange(double a,double b) {
        _Super::setRange(a,b,_0x21Q_decimals);
    }
private:
    CPLUSPLUS_OBJECT(_0x21Q_DoubleValidator)
};

class _0x21Q_IntValidator  :public QIntValidator {
    using _Super=QIntValidator ;
public:
    using _Super::_Super;
private:
    CPLUSPLUS_OBJECT(_0x21Q_IntValidator)
};

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

class RGBADialog::_PrivateRGBADialog{
public:
    RGBADialog *super;
    QVBoxLayout * mainLayout/*主要布局*/;
    _PrivateRGBADialog(RGBADialog *arg):super(arg){
setup_ui()/*建立gui并连接信号槽*/;
readState()/*更新gui数据*/;
}


/*values*/

constexpr static double default_RAlpha_0x2d(){return 1;}
constexpr static double default_step_RAlpha_0x2d(){return 0.2;}
constexpr static double max_RAlpha_0x2d(){return 9999;}
constexpr static double min_RAlpha_0x2d(){return 0;}
double RAlpha_0x2d=default_RAlpha_0x2d();
double step_RAlpha_0x2d=default_step_RAlpha_0x2d();
double old_RAlpha_0x2d=default_RAlpha_0x2d();
_0x21Q_LineEdit * edit_RAlpha_0x2d=nullptr;
_0x21Q_LineEdit * edit_step_RAlpha_0x2d=nullptr;
constexpr static double default_RBeta_0x2d(){return 0;}
constexpr static double default_step_RBeta_0x2d(){return 1.2;}
constexpr static double max_RBeta_0x2d(){return 255;}
constexpr static double min_RBeta_0x2d(){return -255;}
double RBeta_0x2d=default_RBeta_0x2d();
double step_RBeta_0x2d=default_step_RBeta_0x2d();
double old_RBeta_0x2d=default_RBeta_0x2d();
_0x21Q_LineEdit * edit_RBeta_0x2d=nullptr;
_0x21Q_LineEdit * edit_step_RBeta_0x2d=nullptr;
constexpr static double default_GAlpha_0x2d(){return 1;}
constexpr static double default_step_GAlpha_0x2d(){return 0.2;}
constexpr static double max_GAlpha_0x2d(){return 9999;}
constexpr static double min_GAlpha_0x2d(){return 0;}
double GAlpha_0x2d=default_GAlpha_0x2d();
double step_GAlpha_0x2d=default_step_GAlpha_0x2d();
double old_GAlpha_0x2d=default_GAlpha_0x2d();
_0x21Q_LineEdit * edit_GAlpha_0x2d=nullptr;
_0x21Q_LineEdit * edit_step_GAlpha_0x2d=nullptr;
constexpr static double default_GBeta_0x2d(){return 0;}
constexpr static double default_step_GBeta_0x2d(){return 1.2;}
constexpr static double max_GBeta_0x2d(){return 255;}
constexpr static double min_GBeta_0x2d(){return -255;}
double GBeta_0x2d=default_GBeta_0x2d();
double step_GBeta_0x2d=default_step_GBeta_0x2d();
double old_GBeta_0x2d=default_GBeta_0x2d();
_0x21Q_LineEdit * edit_GBeta_0x2d=nullptr;
_0x21Q_LineEdit * edit_step_GBeta_0x2d=nullptr;
constexpr static double default_BAlpha_0x2d(){return 1;}
constexpr static double default_step_BAlpha_0x2d(){return 0.2;}
constexpr static double max_BAlpha_0x2d(){return 9999;}
constexpr static double min_BAlpha_0x2d(){return 0;}
double BAlpha_0x2d=default_BAlpha_0x2d();
double step_BAlpha_0x2d=default_step_BAlpha_0x2d();
double old_BAlpha_0x2d=default_BAlpha_0x2d();
_0x21Q_LineEdit * edit_BAlpha_0x2d=nullptr;
_0x21Q_LineEdit * edit_step_BAlpha_0x2d=nullptr;
constexpr static double default_BBeta_0x2d(){return 0;}
constexpr static double default_step_BBeta_0x2d(){return 1.2;}
constexpr static double max_BBeta_0x2d(){return 255;}
constexpr static double min_BBeta_0x2d(){return -255;}
double BBeta_0x2d=default_BBeta_0x2d();
double step_BBeta_0x2d=default_step_BBeta_0x2d();
double old_BBeta_0x2d=default_BBeta_0x2d();
_0x21Q_LineEdit * edit_BBeta_0x2d=nullptr;
_0x21Q_LineEdit * edit_step_BBeta_0x2d=nullptr;
constexpr static double default_AAlpha_0x2d(){return 1;}
constexpr static double default_step_AAlpha_0x2d(){return 0.2;}
constexpr static double max_AAlpha_0x2d(){return 9999;}
constexpr static double min_AAlpha_0x2d(){return 0;}
double AAlpha_0x2d=default_AAlpha_0x2d();
double step_AAlpha_0x2d=default_step_AAlpha_0x2d();
double old_AAlpha_0x2d=default_AAlpha_0x2d();
_0x21Q_LineEdit * edit_AAlpha_0x2d=nullptr;
_0x21Q_LineEdit * edit_step_AAlpha_0x2d=nullptr;
constexpr static double default_ABeta_0x2d(){return 0;}
constexpr static double default_step_ABeta_0x2d(){return 1.2;}
constexpr static double max_ABeta_0x2d(){return 255;}
constexpr static double min_ABeta_0x2d(){return -255;}
double ABeta_0x2d=default_ABeta_0x2d();
double step_ABeta_0x2d=default_step_ABeta_0x2d();
double old_ABeta_0x2d=default_ABeta_0x2d();
_0x21Q_LineEdit * edit_ABeta_0x2d=nullptr;
_0x21Q_LineEdit * edit_step_ABeta_0x2d=nullptr;
     void setup_ui(){
        using namespace memory ;
/*窗口布局*/
        auto && lv=makeStackPointer<_0x21Q_VBoxLayout>();
        super->setLayout(lv.release());
        lv->setSpacing(0);
        lv->setMargin(0);

/*dialog 主要布局*/
        auto && lvv=makeStackPointer<_0x21Q_VBoxLayout>();
        lvv->setSpacing(0);
        lvv->setMargin(0);
        lv->addLayout(lvv.release());
        mainLayout=lvv.pointer();
///////////////////////////

{

/*创建一个int/double显示*/
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && l1=makeStackPointer<_0x21Q_Label>();
            auto && e0=makeStackPointer<_0x21Q_LineEdit>();
            auto && e1=makeStackPointer<_0x21Q_LineEdit>();
            auto && p0=makeStackPointer<_0x21Q_ToolButton>();
            auto && p1=makeStackPointer<_0x21Q_ToolButton>();
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            lvv->addLayout(l.release())/*加入主要布局*/;
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
l0->setText(u8R"__(RAlpha)__" " : " );/*设置label name*/
edit_RAlpha_0x2d=e0.pointer();
edit_step_RAlpha_0x2d=e1.pointer();

/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
v0->setRange(min_RAlpha_0x2d(),max_RAlpha_0x2d());
v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
edit_RAlpha_0x2d=e0.pointer();
edit_step_RAlpha_0x2d=e1.pointer();

/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_RAlpha_0x2d(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_RAlpha_0x2d(); });
}
{

/*创建一个int/double显示*/
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && l1=makeStackPointer<_0x21Q_Label>();
            auto && e0=makeStackPointer<_0x21Q_LineEdit>();
            auto && e1=makeStackPointer<_0x21Q_LineEdit>();
            auto && p0=makeStackPointer<_0x21Q_ToolButton>();
            auto && p1=makeStackPointer<_0x21Q_ToolButton>();
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            lvv->addLayout(l.release())/*加入主要布局*/;
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
l0->setText(u8R"__(RBeta)__" " : " );/*设置label name*/
edit_RBeta_0x2d=e0.pointer();
edit_step_RBeta_0x2d=e1.pointer();

/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
v0->setRange(min_RBeta_0x2d(),max_RBeta_0x2d());
v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
edit_RBeta_0x2d=e0.pointer();
edit_step_RBeta_0x2d=e1.pointer();

/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_RBeta_0x2d(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_RBeta_0x2d(); });
}
{

/*创建一个int/double显示*/
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && l1=makeStackPointer<_0x21Q_Label>();
            auto && e0=makeStackPointer<_0x21Q_LineEdit>();
            auto && e1=makeStackPointer<_0x21Q_LineEdit>();
            auto && p0=makeStackPointer<_0x21Q_ToolButton>();
            auto && p1=makeStackPointer<_0x21Q_ToolButton>();
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            lvv->addLayout(l.release())/*加入主要布局*/;
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
l0->setText(u8R"__(GAlpha)__" " : " );/*设置label name*/
edit_GAlpha_0x2d=e0.pointer();
edit_step_GAlpha_0x2d=e1.pointer();

/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
v0->setRange(min_GAlpha_0x2d(),max_GAlpha_0x2d());
v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
edit_GAlpha_0x2d=e0.pointer();
edit_step_GAlpha_0x2d=e1.pointer();

/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_GAlpha_0x2d(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_GAlpha_0x2d(); });
}
{

/*创建一个int/double显示*/
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && l1=makeStackPointer<_0x21Q_Label>();
            auto && e0=makeStackPointer<_0x21Q_LineEdit>();
            auto && e1=makeStackPointer<_0x21Q_LineEdit>();
            auto && p0=makeStackPointer<_0x21Q_ToolButton>();
            auto && p1=makeStackPointer<_0x21Q_ToolButton>();
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            lvv->addLayout(l.release())/*加入主要布局*/;
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
l0->setText(u8R"__(GBeta)__" " : " );/*设置label name*/
edit_GBeta_0x2d=e0.pointer();
edit_step_GBeta_0x2d=e1.pointer();

/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
v0->setRange(min_GBeta_0x2d(),max_GBeta_0x2d());
v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
edit_GBeta_0x2d=e0.pointer();
edit_step_GBeta_0x2d=e1.pointer();

/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_GBeta_0x2d(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_GBeta_0x2d(); });
}
{

/*创建一个int/double显示*/
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && l1=makeStackPointer<_0x21Q_Label>();
            auto && e0=makeStackPointer<_0x21Q_LineEdit>();
            auto && e1=makeStackPointer<_0x21Q_LineEdit>();
            auto && p0=makeStackPointer<_0x21Q_ToolButton>();
            auto && p1=makeStackPointer<_0x21Q_ToolButton>();
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            lvv->addLayout(l.release())/*加入主要布局*/;
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
l0->setText(u8R"__(BAlpha)__" " : " );/*设置label name*/
edit_BAlpha_0x2d=e0.pointer();
edit_step_BAlpha_0x2d=e1.pointer();

/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
v0->setRange(min_BAlpha_0x2d(),max_BAlpha_0x2d());
v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
edit_BAlpha_0x2d=e0.pointer();
edit_step_BAlpha_0x2d=e1.pointer();

/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_BAlpha_0x2d(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_BAlpha_0x2d(); });
}
{

/*创建一个int/double显示*/
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && l1=makeStackPointer<_0x21Q_Label>();
            auto && e0=makeStackPointer<_0x21Q_LineEdit>();
            auto && e1=makeStackPointer<_0x21Q_LineEdit>();
            auto && p0=makeStackPointer<_0x21Q_ToolButton>();
            auto && p1=makeStackPointer<_0x21Q_ToolButton>();
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            lvv->addLayout(l.release())/*加入主要布局*/;
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
l0->setText(u8R"__(BBeta)__" " : " );/*设置label name*/
edit_BBeta_0x2d=e0.pointer();
edit_step_BBeta_0x2d=e1.pointer();

/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
v0->setRange(min_BBeta_0x2d(),max_BBeta_0x2d());
v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
edit_BBeta_0x2d=e0.pointer();
edit_step_BBeta_0x2d=e1.pointer();

/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_BBeta_0x2d(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_BBeta_0x2d(); });
}
{

/*创建一个int/double显示*/
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && l1=makeStackPointer<_0x21Q_Label>();
            auto && e0=makeStackPointer<_0x21Q_LineEdit>();
            auto && e1=makeStackPointer<_0x21Q_LineEdit>();
            auto && p0=makeStackPointer<_0x21Q_ToolButton>();
            auto && p1=makeStackPointer<_0x21Q_ToolButton>();
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            lvv->addLayout(l.release())/*加入主要布局*/;
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
l0->setText(u8R"__(AAlpha)__" " : " );/*设置label name*/
edit_AAlpha_0x2d=e0.pointer();
edit_step_AAlpha_0x2d=e1.pointer();

/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
v0->setRange(min_AAlpha_0x2d(),max_AAlpha_0x2d());
v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
edit_AAlpha_0x2d=e0.pointer();
edit_step_AAlpha_0x2d=e1.pointer();

/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_AAlpha_0x2d(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_AAlpha_0x2d(); });
}
{

/*创建一个int/double显示*/
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && l1=makeStackPointer<_0x21Q_Label>();
            auto && e0=makeStackPointer<_0x21Q_LineEdit>();
            auto && e1=makeStackPointer<_0x21Q_LineEdit>();
            auto && p0=makeStackPointer<_0x21Q_ToolButton>();
            auto && p1=makeStackPointer<_0x21Q_ToolButton>();
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            lvv->addLayout(l.release())/*加入主要布局*/;
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
l0->setText(u8R"__(ABeta)__" " : " );/*设置label name*/
edit_ABeta_0x2d=e0.pointer();
edit_step_ABeta_0x2d=e1.pointer();

/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
v0->setRange(min_ABeta_0x2d(),max_ABeta_0x2d());
v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
edit_ABeta_0x2d=e0.pointer();
edit_step_ABeta_0x2d=e1.pointer();

/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_ABeta_0x2d(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_ABeta_0x2d(); });
}

{/*创建中间空白*/
            auto && ls=makeStackPointer<_0x21Q_SpacerItem>(
                1,1,QSizePolicy::Minimum,
                QSizePolicy::MinimumExpanding
                );
            lv->addSpacerItem(ls.release());
        }
{/*创建确定按钮*/
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            l->setSpacing(1);
            l->setMargin(1);
            auto && ls=makeStackPointer<_0x21Q_SpacerItem>(
                1,1,QSizePolicy::MinimumExpanding,
                QSizePolicy::Minimum);
            l->addSpacerItem(ls.release());
            auto && pb=makeStackPointer<_0x21Q_PushButton>();
            l->addWidget(pb.release());
            lv->addLayout(l.release());
            pb->setText(QString::fromUtf8(u8"确定"));
/*连接按钮信号槽*/
         
 super->connect(
                        pb.pointer(),
                        &QPushButton::clicked,
                        super,
                        [this](bool){checkDo();}
                        );

}

}/*function end*/
void readState() {
bool ok;
do{
auto t=edit_RAlpha_0x2d->text();
RAlpha_0x2d= t.toDouble(&ok);
if (ok) { break; }
RAlpha_0x2d=default_RAlpha_0x2d();
edit_RAlpha_0x2d->setText(
QString::number(default_RAlpha_0x2d()));
} while (false);
do{
auto t=edit_step_RAlpha_0x2d->text();
step_RAlpha_0x2d= t.toDouble(&ok);
if (ok) { break; }
step_RAlpha_0x2d=default_step_RAlpha_0x2d();
edit_step_RAlpha_0x2d->setText(
QString::number(default_step_RAlpha_0x2d()));
} while (false);
do{
auto t=edit_RBeta_0x2d->text();
RBeta_0x2d= t.toDouble(&ok);
if (ok) { break; }
RBeta_0x2d=default_RBeta_0x2d();
edit_RBeta_0x2d->setText(
QString::number(default_RBeta_0x2d()));
} while (false);
do{
auto t=edit_step_RBeta_0x2d->text();
step_RBeta_0x2d= t.toDouble(&ok);
if (ok) { break; }
step_RBeta_0x2d=default_step_RBeta_0x2d();
edit_step_RBeta_0x2d->setText(
QString::number(default_step_RBeta_0x2d()));
} while (false);
do{
auto t=edit_GAlpha_0x2d->text();
GAlpha_0x2d= t.toDouble(&ok);
if (ok) { break; }
GAlpha_0x2d=default_GAlpha_0x2d();
edit_GAlpha_0x2d->setText(
QString::number(default_GAlpha_0x2d()));
} while (false);
do{
auto t=edit_step_GAlpha_0x2d->text();
step_GAlpha_0x2d= t.toDouble(&ok);
if (ok) { break; }
step_GAlpha_0x2d=default_step_GAlpha_0x2d();
edit_step_GAlpha_0x2d->setText(
QString::number(default_step_GAlpha_0x2d()));
} while (false);
do{
auto t=edit_GBeta_0x2d->text();
GBeta_0x2d= t.toDouble(&ok);
if (ok) { break; }
GBeta_0x2d=default_GBeta_0x2d();
edit_GBeta_0x2d->setText(
QString::number(default_GBeta_0x2d()));
} while (false);
do{
auto t=edit_step_GBeta_0x2d->text();
step_GBeta_0x2d= t.toDouble(&ok);
if (ok) { break; }
step_GBeta_0x2d=default_step_GBeta_0x2d();
edit_step_GBeta_0x2d->setText(
QString::number(default_step_GBeta_0x2d()));
} while (false);
do{
auto t=edit_BAlpha_0x2d->text();
BAlpha_0x2d= t.toDouble(&ok);
if (ok) { break; }
BAlpha_0x2d=default_BAlpha_0x2d();
edit_BAlpha_0x2d->setText(
QString::number(default_BAlpha_0x2d()));
} while (false);
do{
auto t=edit_step_BAlpha_0x2d->text();
step_BAlpha_0x2d= t.toDouble(&ok);
if (ok) { break; }
step_BAlpha_0x2d=default_step_BAlpha_0x2d();
edit_step_BAlpha_0x2d->setText(
QString::number(default_step_BAlpha_0x2d()));
} while (false);
do{
auto t=edit_BBeta_0x2d->text();
BBeta_0x2d= t.toDouble(&ok);
if (ok) { break; }
BBeta_0x2d=default_BBeta_0x2d();
edit_BBeta_0x2d->setText(
QString::number(default_BBeta_0x2d()));
} while (false);
do{
auto t=edit_step_BBeta_0x2d->text();
step_BBeta_0x2d= t.toDouble(&ok);
if (ok) { break; }
step_BBeta_0x2d=default_step_BBeta_0x2d();
edit_step_BBeta_0x2d->setText(
QString::number(default_step_BBeta_0x2d()));
} while (false);
do{
auto t=edit_AAlpha_0x2d->text();
AAlpha_0x2d= t.toDouble(&ok);
if (ok) { break; }
AAlpha_0x2d=default_AAlpha_0x2d();
edit_AAlpha_0x2d->setText(
QString::number(default_AAlpha_0x2d()));
} while (false);
do{
auto t=edit_step_AAlpha_0x2d->text();
step_AAlpha_0x2d= t.toDouble(&ok);
if (ok) { break; }
step_AAlpha_0x2d=default_step_AAlpha_0x2d();
edit_step_AAlpha_0x2d->setText(
QString::number(default_step_AAlpha_0x2d()));
} while (false);
do{
auto t=edit_ABeta_0x2d->text();
ABeta_0x2d= t.toDouble(&ok);
if (ok) { break; }
ABeta_0x2d=default_ABeta_0x2d();
edit_ABeta_0x2d->setText(
QString::number(default_ABeta_0x2d()));
} while (false);
do{
auto t=edit_step_ABeta_0x2d->text();
step_ABeta_0x2d= t.toDouble(&ok);
if (ok) { break; }
step_ABeta_0x2d=default_step_ABeta_0x2d();
edit_step_ABeta_0x2d->setText(
QString::number(default_step_ABeta_0x2d()));
} while (false);
}
void directDo() {
super->valueChanged(RAlpha_0x2d
,RBeta_0x2d
,GAlpha_0x2d
,GBeta_0x2d
,BAlpha_0x2d
,BBeta_0x2d
,AAlpha_0x2d
,ABeta_0x2d);
}
 bool isStateChange() {
 auto ans=false;
if (old_RAlpha_0x2d!=RAlpha_0x2d){
ans=true;
old_RAlpha_0x2d=RAlpha_0x2d;
}
if (old_RBeta_0x2d!=RBeta_0x2d){
ans=true;
old_RBeta_0x2d=RBeta_0x2d;
}
if (old_GAlpha_0x2d!=GAlpha_0x2d){
ans=true;
old_GAlpha_0x2d=GAlpha_0x2d;
}
if (old_GBeta_0x2d!=GBeta_0x2d){
ans=true;
old_GBeta_0x2d=GBeta_0x2d;
}
if (old_BAlpha_0x2d!=BAlpha_0x2d){
ans=true;
old_BAlpha_0x2d=BAlpha_0x2d;
}
if (old_BBeta_0x2d!=BBeta_0x2d){
ans=true;
old_BBeta_0x2d=BBeta_0x2d;
}
if (old_AAlpha_0x2d!=AAlpha_0x2d){
ans=true;
old_AAlpha_0x2d=AAlpha_0x2d;
}
if (old_ABeta_0x2d!=ABeta_0x2d){
ans=true;
old_ABeta_0x2d=ABeta_0x2d;
}
return ans;
}


 void checkDo(){
         readState();
         if(isStateChange()){
            directDo();
         }
    }

    template<typename _T_,typename _U_>
    static void check_max(_T_ & v,const _U_&m) {
        if (v>m) { v=m; }
    }

    template<typename _T_,typename _U_>
    static void check_min(_T_ & v,const _U_&m) {
        if (v<m) { v=m; }
    }


 void add_RAlpha_0x2d() {
        readState()/*获得当前状态*/;
        RAlpha_0x2d+=step_RAlpha_0x2d/*增加值*/;
        check_max(RAlpha_0x2d,max_RAlpha_0x2d())/*检测最大值*/;
        check_min(RAlpha_0x2d,min_RAlpha_0x2d())/*检测最小值*/;
        edit_RAlpha_0x2d->setText(
            QString::number(RAlpha_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void sub_RAlpha_0x2d() {
        readState()/*获得当前状态*/;
        RAlpha_0x2d-=step_RAlpha_0x2d/*增加值*/;
        check_max(RAlpha_0x2d,max_RAlpha_0x2d())/*检测最大值*/;
        check_min(RAlpha_0x2d,min_RAlpha_0x2d())/*检测最小值*/;
        edit_RAlpha_0x2d->setText(
            QString::number(RAlpha_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void add_RBeta_0x2d() {
        readState()/*获得当前状态*/;
        RBeta_0x2d+=step_RBeta_0x2d/*增加值*/;
        check_max(RBeta_0x2d,max_RBeta_0x2d())/*检测最大值*/;
        check_min(RBeta_0x2d,min_RBeta_0x2d())/*检测最小值*/;
        edit_RBeta_0x2d->setText(
            QString::number(RBeta_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void sub_RBeta_0x2d() {
        readState()/*获得当前状态*/;
        RBeta_0x2d-=step_RBeta_0x2d/*增加值*/;
        check_max(RBeta_0x2d,max_RBeta_0x2d())/*检测最大值*/;
        check_min(RBeta_0x2d,min_RBeta_0x2d())/*检测最小值*/;
        edit_RBeta_0x2d->setText(
            QString::number(RBeta_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void add_GAlpha_0x2d() {
        readState()/*获得当前状态*/;
        GAlpha_0x2d+=step_GAlpha_0x2d/*增加值*/;
        check_max(GAlpha_0x2d,max_GAlpha_0x2d())/*检测最大值*/;
        check_min(GAlpha_0x2d,min_GAlpha_0x2d())/*检测最小值*/;
        edit_GAlpha_0x2d->setText(
            QString::number(GAlpha_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void sub_GAlpha_0x2d() {
        readState()/*获得当前状态*/;
        GAlpha_0x2d-=step_GAlpha_0x2d/*增加值*/;
        check_max(GAlpha_0x2d,max_GAlpha_0x2d())/*检测最大值*/;
        check_min(GAlpha_0x2d,min_GAlpha_0x2d())/*检测最小值*/;
        edit_GAlpha_0x2d->setText(
            QString::number(GAlpha_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void add_GBeta_0x2d() {
        readState()/*获得当前状态*/;
        GBeta_0x2d+=step_GBeta_0x2d/*增加值*/;
        check_max(GBeta_0x2d,max_GBeta_0x2d())/*检测最大值*/;
        check_min(GBeta_0x2d,min_GBeta_0x2d())/*检测最小值*/;
        edit_GBeta_0x2d->setText(
            QString::number(GBeta_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void sub_GBeta_0x2d() {
        readState()/*获得当前状态*/;
        GBeta_0x2d-=step_GBeta_0x2d/*增加值*/;
        check_max(GBeta_0x2d,max_GBeta_0x2d())/*检测最大值*/;
        check_min(GBeta_0x2d,min_GBeta_0x2d())/*检测最小值*/;
        edit_GBeta_0x2d->setText(
            QString::number(GBeta_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void add_BAlpha_0x2d() {
        readState()/*获得当前状态*/;
        BAlpha_0x2d+=step_BAlpha_0x2d/*增加值*/;
        check_max(BAlpha_0x2d,max_BAlpha_0x2d())/*检测最大值*/;
        check_min(BAlpha_0x2d,min_BAlpha_0x2d())/*检测最小值*/;
        edit_BAlpha_0x2d->setText(
            QString::number(BAlpha_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void sub_BAlpha_0x2d() {
        readState()/*获得当前状态*/;
        BAlpha_0x2d-=step_BAlpha_0x2d/*增加值*/;
        check_max(BAlpha_0x2d,max_BAlpha_0x2d())/*检测最大值*/;
        check_min(BAlpha_0x2d,min_BAlpha_0x2d())/*检测最小值*/;
        edit_BAlpha_0x2d->setText(
            QString::number(BAlpha_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void add_BBeta_0x2d() {
        readState()/*获得当前状态*/;
        BBeta_0x2d+=step_BBeta_0x2d/*增加值*/;
        check_max(BBeta_0x2d,max_BBeta_0x2d())/*检测最大值*/;
        check_min(BBeta_0x2d,min_BBeta_0x2d())/*检测最小值*/;
        edit_BBeta_0x2d->setText(
            QString::number(BBeta_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void sub_BBeta_0x2d() {
        readState()/*获得当前状态*/;
        BBeta_0x2d-=step_BBeta_0x2d/*增加值*/;
        check_max(BBeta_0x2d,max_BBeta_0x2d())/*检测最大值*/;
        check_min(BBeta_0x2d,min_BBeta_0x2d())/*检测最小值*/;
        edit_BBeta_0x2d->setText(
            QString::number(BBeta_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void add_AAlpha_0x2d() {
        readState()/*获得当前状态*/;
        AAlpha_0x2d+=step_AAlpha_0x2d/*增加值*/;
        check_max(AAlpha_0x2d,max_AAlpha_0x2d())/*检测最大值*/;
        check_min(AAlpha_0x2d,min_AAlpha_0x2d())/*检测最小值*/;
        edit_AAlpha_0x2d->setText(
            QString::number(AAlpha_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void sub_AAlpha_0x2d() {
        readState()/*获得当前状态*/;
        AAlpha_0x2d-=step_AAlpha_0x2d/*增加值*/;
        check_max(AAlpha_0x2d,max_AAlpha_0x2d())/*检测最大值*/;
        check_min(AAlpha_0x2d,min_AAlpha_0x2d())/*检测最小值*/;
        edit_AAlpha_0x2d->setText(
            QString::number(AAlpha_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void add_ABeta_0x2d() {
        readState()/*获得当前状态*/;
        ABeta_0x2d+=step_ABeta_0x2d/*增加值*/;
        check_max(ABeta_0x2d,max_ABeta_0x2d())/*检测最大值*/;
        check_min(ABeta_0x2d,min_ABeta_0x2d())/*检测最小值*/;
        edit_ABeta_0x2d->setText(
            QString::number(ABeta_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

 void sub_ABeta_0x2d() {
        readState()/*获得当前状态*/;
        ABeta_0x2d-=step_ABeta_0x2d/*增加值*/;
        check_max(ABeta_0x2d,max_ABeta_0x2d())/*检测最大值*/;
        check_min(ABeta_0x2d,min_ABeta_0x2d())/*检测最小值*/;
        edit_ABeta_0x2d->setText(
            QString::number(ABeta_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }


private:
    CPLUSPLUS_OBJECT(_PrivateRGBADialog)
};

RGBADialog::RGBADialog(QWidget *p):_Super(p){
    thisp=new _PrivateRGBADialog(this);
}

RGBADialog::~RGBADialog(){
    delete thisp;
}

void RGBADialog::emitValueChanged() {
    thisp->readState();
    thisp->directDo();
}

QSize RGBADialog::sizeHint() const {
    return {136,128};
}

QVBoxLayout * RGBADialog::getMainLayout() const {
    return thisp->mainLayout;
}

/*End of the file.*/


