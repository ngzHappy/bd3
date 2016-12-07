﻿#include "VortexDialog.hpp"
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

namespace {

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
        _Super(-360,360,_0x21Q_decimals,arg) {
        setNotation(QDoubleValidator::StandardNotation);
    }
    void setRange(double a,double b) {
        _Super::setRange(a,b,_0x21Q_decimals);
    }
private:
    CPLUSPLUS_OBJECT(_0x21Q_DoubleValidator)
};

class _0x21Q_IntValidator :public QIntValidator {
    using _Super=QIntValidator;
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

class VortexDialog::_PrivateVortexDialog {
public:
    VortexDialog *super;
    QVBoxLayout * mainLayout/*主要布局*/;
    _PrivateVortexDialog(VortexDialog *arg):super(arg) {
        setup_ui()/*建立gui并连接信号槽*/;
        readState()/*更新gui数据*/;
    }


    /*values*/

    constexpr static double default_radius_0x2d() { return 50; }
    constexpr static double default_step_radius_0x2d() { return 1.2; }
    constexpr static double max_radius_0x2d() { return 9999; }
    constexpr static double min_radius_0x2d() { return 0; }
    double radius_0x2d=default_radius_0x2d();
    double step_radius_0x2d=default_step_radius_0x2d();
    double old_radius_0x2d=default_radius_0x2d();
    _0x21Q_LineEdit * edit_radius_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step_radius_0x2d=nullptr;
    constexpr static double default_rate_0x2d() { return 10; }
    constexpr static double default_step_rate_0x2d() { return 0.05; }
    constexpr static double max_rate_0x2d() { return 9999; }
    constexpr static double min_rate_0x2d() { return 1e-5; }
    double rate_0x2d=default_rate_0x2d();
    double step_rate_0x2d=default_step_rate_0x2d();
    double old_rate_0x2d=default_rate_0x2d();
    _0x21Q_LineEdit * edit_rate_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step_rate_0x2d=nullptr;
    void setup_ui() {
        using namespace memory;
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
            l0->setText(u8R"__(radius)__" " : ");/*设置label name*/
            edit_radius_0x2d=e0.pointer();
            edit_step_radius_0x2d=e1.pointer();

            /*double value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
            auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
            v0->setRange(min_radius_0x2d(),max_radius_0x2d());
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_radius_0x2d=e0.pointer();
            edit_step_radius_0x2d=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_radius_0x2d(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_radius_0x2d(); });
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
            l0->setText(u8R"__(rate)__" " : ");/*设置label name*/
            edit_rate_0x2d=e0.pointer();
            edit_step_rate_0x2d=e1.pointer();

            /*double value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
            auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
            v0->setRange(min_rate_0x2d(),max_rate_0x2d());
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_rate_0x2d=e0.pointer();
            edit_step_rate_0x2d=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_rate_0x2d(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_rate_0x2d(); });
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
                                   [this](bool) {checkDo(); }
            );

        }

    }/*function end*/
    void readState() {
        bool ok;
        do {
            auto t=edit_radius_0x2d->text();
            radius_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            radius_0x2d=default_radius_0x2d();
            edit_radius_0x2d->setText(
            QString::number(default_radius_0x2d()));
        } while (false);
        do {
            auto t=edit_step_radius_0x2d->text();
            step_radius_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            step_radius_0x2d=default_step_radius_0x2d();
            edit_step_radius_0x2d->setText(
            QString::number(default_step_radius_0x2d()));
        } while (false);
        do {
            auto t=edit_rate_0x2d->text();
            rate_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            rate_0x2d=default_rate_0x2d();
            edit_rate_0x2d->setText(
            QString::number(default_rate_0x2d()));
        } while (false);
        do {
            auto t=edit_step_rate_0x2d->text();
            step_rate_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            step_rate_0x2d=default_step_rate_0x2d();
            edit_step_rate_0x2d->setText(
            QString::number(default_step_rate_0x2d()));
        } while (false);
    }
    void directDo() {
        super->valueChanged(radius_0x2d
        ,rate_0x2d);
    }
    bool isStateChange() {
        auto ans=false;
        if (old_radius_0x2d!=radius_0x2d) {
            ans=true;
            old_radius_0x2d=radius_0x2d;
        }
        if (old_rate_0x2d!=rate_0x2d) {
            ans=true;
            old_rate_0x2d=rate_0x2d;
        }
        return ans;
    }


    void checkDo() {
        readState();
        if (isStateChange()) {
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


    void add_radius_0x2d() {
        readState()/*获得当前状态*/;
        radius_0x2d+=step_radius_0x2d/*增加值*/;
        check_max(radius_0x2d,max_radius_0x2d())/*检测最大值*/;
        check_min(radius_0x2d,min_radius_0x2d())/*检测最小值*/;
        edit_radius_0x2d->setText(
            QString::number(radius_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_radius_0x2d() {
        readState()/*获得当前状态*/;
        radius_0x2d-=step_radius_0x2d/*增加值*/;
        check_max(radius_0x2d,max_radius_0x2d())/*检测最大值*/;
        check_min(radius_0x2d,min_radius_0x2d())/*检测最小值*/;
        edit_radius_0x2d->setText(
            QString::number(radius_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_rate_0x2d() {
        readState()/*获得当前状态*/;
        rate_0x2d+=step_rate_0x2d/*增加值*/;
        check_max(rate_0x2d,max_rate_0x2d())/*检测最大值*/;
        check_min(rate_0x2d,min_rate_0x2d())/*检测最小值*/;
        edit_rate_0x2d->setText(
            QString::number(rate_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_rate_0x2d() {
        readState()/*获得当前状态*/;
        rate_0x2d-=step_rate_0x2d/*增加值*/;
        check_max(rate_0x2d,max_rate_0x2d())/*检测最大值*/;
        check_min(rate_0x2d,min_rate_0x2d())/*检测最小值*/;
        edit_rate_0x2d->setText(
            QString::number(rate_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }


private:
    CPLUSPLUS_OBJECT(_PrivateVortexDialog)
};

VortexDialog::VortexDialog(QWidget *p):_Super(p) {
    thisp=new _PrivateVortexDialog(this);
}

VortexDialog::~VortexDialog() {
    delete thisp;
}

void VortexDialog::emitValueChanged() {
    thisp->readState();
    thisp->directDo();
}

QSize VortexDialog::sizeHint() const {
    return{ 123+136,128 };
}

QVBoxLayout * VortexDialog::getMainLayout() const {
    return thisp->mainLayout;
}

/*End of the file.*/


