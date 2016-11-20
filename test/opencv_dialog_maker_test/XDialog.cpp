#include "XDialog.hpp"
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

class Step_0x21Q_DoubleValidator :public QDoubleValidator {
    using _Super=QDoubleValidator;
public:
    Step_0x21Q_DoubleValidator():_Super(-9999,9999,6) {
        setNotation(QDoubleValidator::StandardNotation);
    }
private:
    CPLUSPLUS_OBJECT(Step_0x21Q_DoubleValidator)
};

class _0x21Q_DoubleValidator :public QDoubleValidator {
    using _Super=QDoubleValidator;
public:
    using _Super::_Super;
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

class XDialog::_PrivateXDialog {
public:
    XDialog *super;
    _PrivateXDialog(XDialog *arg):super(arg) {
        setup_ui()/*建立gui并连接信号槽*/;
        readState()/*更新gui数据*/;
    }


    /*values*/

    constexpr static int default__x_Dialogtest0_0x2i() { return 22; }
    constexpr static int default_step__x_Dialogtest0_0x2i() { return 1; }
    constexpr static int max__x_Dialogtest0_0x2i() { return 30; }
    constexpr static int min__x_Dialogtest0_0x2i() { return 10; }
    int _x_Dialogtest0_0x2i=default__x_Dialogtest0_0x2i();
    int step__x_Dialogtest0_0x2i=default_step__x_Dialogtest0_0x2i();
    int old__x_Dialogtest0_0x2i=default__x_Dialogtest0_0x2i();
    _0x21Q_LineEdit * edit__x_Dialogtest0_0x2i=nullptr;
    _0x21Q_LineEdit * edit_step__x_Dialogtest0_0x2i=nullptr;
    constexpr static double default__x_Dialogtest1_0x2d() { return 22.1; }
    constexpr static double default_step__x_Dialogtest1_0x2d() { return 0.1; }
    constexpr static double max__x_Dialogtest1_0x2d() { return 30.3; }
    constexpr static double min__x_Dialogtest1_0x2d() { return 10.2; }
    double _x_Dialogtest1_0x2d=default__x_Dialogtest1_0x2d();
    double step__x_Dialogtest1_0x2d=default_step__x_Dialogtest1_0x2d();
    double old__x_Dialogtest1_0x2d=default__x_Dialogtest1_0x2d();
    _0x21Q_LineEdit * edit__x_Dialogtest1_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step__x_Dialogtest1_0x2d=nullptr;
    _0x21Q_ComboBox * enum__x_Dialogtest2_0x2e=nullptr;
    int/*enum*/old__x_Dialogtest2_0x2e=static_cast<int/*enum*/>(9);
    int/*enum*/_x_Dialogtest2_0x2e=static_cast<int/*enum*/>(9);
    int/*enum*/map__x_Dialogtest2_0x2e(int arg) {
        switch (arg) {

            case 0: return static_cast<int/*enum*/>(9);/* a */
            case 1: return static_cast<int/*enum*/>(2);/* b */
        }
        return static_cast<int/*enum*/>(9);/*默认值*/
    }

    void setup_ui() {
        using namespace memory;
        /*窗口布局*/
        auto && lv=makeStackPointer<_0x21Q_VBoxLayout>();
        super->setLayout(lv.release());
        lv->setSpacing(0);
        lv->setMargin(0);

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
            lv->addLayout(l.release());
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
            l0->setText(u8R"__(XDialogtest0)__" " : ");/*设置label name*/
            edit__x_Dialogtest0_0x2i=e0.pointer();
            edit_step__x_Dialogtest0_0x2i=e1.pointer();

            /*int value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_IntValidator>();
            auto && v1=makeStackPointer<_0x21Q_IntValidator>();
            v0->setRange(min__x_Dialogtest0_0x2i(),max__x_Dialogtest0_0x2i());
            v1->setRange(-9999,9999);
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit__x_Dialogtest0_0x2i=e0.pointer();
            edit_step__x_Dialogtest0_0x2i=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
                /*连接信号槽*/super,[this](bool) {add__x_Dialogtest0_0x2i(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
                /*连接信号槽*/super,[this](bool) {sub__x_Dialogtest0_0x2i(); });
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
            lv->addLayout(l.release());
            l->addWidget(l0.release());
            l->addWidget(e0.release());
            l->addWidget(l1.release());
            l->addWidget(e1.release());
            l->addWidget(p0.release());
            l->addWidget(p1.release());
            l1->setText("step:");
            p0->setText("+");
            p1->setText("-");
            l0->setText(u8R"__(XDialogtest1)__" " : ");/*设置label name*/
            edit__x_Dialogtest1_0x2d=e0.pointer();
            edit_step__x_Dialogtest1_0x2d=e1.pointer();

            /*double value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
            auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
            v0->setRange(min__x_Dialogtest1_0x2d(),max__x_Dialogtest1_0x2d());
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit__x_Dialogtest1_0x2d=e0.pointer();
            edit_step__x_Dialogtest1_0x2d=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
                /*连接信号槽*/super,[this](bool) {add__x_Dialogtest1_0x2d(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
                /*连接信号槽*/super,[this](bool) {sub__x_Dialogtest1_0x2d(); });
        }
        {

            /*创建一个enum选择器*/
            auto && l=makeStackPointer<_0x21Q_HBoxLayout>();
            auto && l0=makeStackPointer<_0x21Q_Label>();
            auto && c0=makeStackPointer<_0x21Q_ComboBox>();
            l0->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,
                QSizePolicy::Minimum));
            c0->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
                QSizePolicy::Minimum));
            l->setSpacing(1);
            l->setMargin(1);
            l->addWidget(l0.release());
            l->addWidget(c0.release());
            lv->addLayout(l.release());

            l0->setText(u8R"__(XDialogtest2)__" " : ");/*设置label name*/

            c0->addItem(u8R"|||(a)|||");
            c0->addItem(u8R"|||(b)|||");
            /*连接信号槽*/
            c0->connect(c0.pointer(),
                T_0x21Q_CurrentIndexChanged(&QComboBox::currentIndexChanged),
                super,
                [this](int) {checkDo(); });
            enum__x_Dialogtest2_0x2e=c0;

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
            auto t=edit__x_Dialogtest0_0x2i->text();
            _x_Dialogtest0_0x2i=t.toInt(&ok);
            if (ok) { break; }
            _x_Dialogtest0_0x2i=default__x_Dialogtest0_0x2i();
            edit__x_Dialogtest0_0x2i->setText(
                QString::number(default__x_Dialogtest0_0x2i()));
        } while (false);
        do {
            auto t=edit_step__x_Dialogtest0_0x2i->text();
            step__x_Dialogtest0_0x2i=t.toInt(&ok);
            if (ok) { break; }
            step__x_Dialogtest0_0x2i=default_step__x_Dialogtest0_0x2i();
            edit_step__x_Dialogtest0_0x2i->setText(
                QString::number(default_step__x_Dialogtest0_0x2i()));
        } while (false);
        do {
            auto t=edit__x_Dialogtest1_0x2d->text();
            _x_Dialogtest1_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            _x_Dialogtest1_0x2d=default__x_Dialogtest1_0x2d();
            edit__x_Dialogtest1_0x2d->setText(
                QString::number(default__x_Dialogtest1_0x2d()));
        } while (false);
        do {
            auto t=edit_step__x_Dialogtest1_0x2d->text();
            step__x_Dialogtest1_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            step__x_Dialogtest1_0x2d=default_step__x_Dialogtest1_0x2d();
            edit_step__x_Dialogtest1_0x2d->setText(
                QString::number(default_step__x_Dialogtest1_0x2d()));
        } while (false);

        {_x_Dialogtest2_0x2e=map__x_Dialogtest2_0x2e(
            enum__x_Dialogtest2_0x2e->currentIndex()); }
    }
    void directDo() {
        super->valueChanged(_x_Dialogtest0_0x2i
            ,_x_Dialogtest1_0x2d
            ,_x_Dialogtest2_0x2e);
    }
    bool isStateChange() {
        auto ans=false;
        if (old__x_Dialogtest0_0x2i!=_x_Dialogtest0_0x2i) {
            ans=true;
            old__x_Dialogtest0_0x2i=_x_Dialogtest0_0x2i;
        }
        if (old__x_Dialogtest1_0x2d!=_x_Dialogtest1_0x2d) {
            ans=true;
            old__x_Dialogtest1_0x2d=_x_Dialogtest1_0x2d;
        }
        if (old__x_Dialogtest2_0x2e!=_x_Dialogtest2_0x2e) {
            ans=true;
            old__x_Dialogtest2_0x2e=_x_Dialogtest2_0x2e;
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


    void add__x_Dialogtest0_0x2i() {
        readState()/*获得当前状态*/;
        _x_Dialogtest0_0x2i+=step__x_Dialogtest0_0x2i/*增加值*/;
        check_max(_x_Dialogtest0_0x2i,max__x_Dialogtest0_0x2i())/*检测最大值*/;
        check_min(_x_Dialogtest0_0x2i,min__x_Dialogtest0_0x2i())/*检测最小值*/;
        edit__x_Dialogtest0_0x2i->setText(
            QString::number(_x_Dialogtest0_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub__x_Dialogtest0_0x2i() {
        readState()/*获得当前状态*/;
        _x_Dialogtest0_0x2i-=step__x_Dialogtest0_0x2i/*增加值*/;
        check_max(_x_Dialogtest0_0x2i,max__x_Dialogtest0_0x2i())/*检测最大值*/;
        check_min(_x_Dialogtest0_0x2i,min__x_Dialogtest0_0x2i())/*检测最小值*/;
        edit__x_Dialogtest0_0x2i->setText(
            QString::number(_x_Dialogtest0_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add__x_Dialogtest1_0x2d() {
        readState()/*获得当前状态*/;
        _x_Dialogtest1_0x2d+=step__x_Dialogtest1_0x2d/*增加值*/;
        check_max(_x_Dialogtest1_0x2d,max__x_Dialogtest1_0x2d())/*检测最大值*/;
        check_min(_x_Dialogtest1_0x2d,min__x_Dialogtest1_0x2d())/*检测最小值*/;
        edit__x_Dialogtest1_0x2d->setText(
            QString::number(_x_Dialogtest1_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub__x_Dialogtest1_0x2d() {
        readState()/*获得当前状态*/;
        _x_Dialogtest1_0x2d-=step__x_Dialogtest1_0x2d/*增加值*/;
        check_max(_x_Dialogtest1_0x2d,max__x_Dialogtest1_0x2d())/*检测最大值*/;
        check_min(_x_Dialogtest1_0x2d,min__x_Dialogtest1_0x2d())/*检测最小值*/;
        edit__x_Dialogtest1_0x2d->setText(
            QString::number(_x_Dialogtest1_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }


private:
    CPLUSPLUS_OBJECT(_PrivateXDialog)
};

XDialog::XDialog(QWidget *p):_Super(p) {
    thisp=new _PrivateXDialog(this);
}

XDialog::~XDialog() {
    delete thisp;
}

void XDialog::emitValueChanged() {
    thisp->directDo();
}

