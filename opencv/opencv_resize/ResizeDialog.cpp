#include "ResizeDialog.hpp"
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

class ResizeDialog::_PrivateResizeDialog {
public:
    ResizeDialog *super;
    QVBoxLayout * mainLayout/*主要布局*/;
    _PrivateResizeDialog(ResizeDialog *arg):super(arg) {
        setup_ui()/*建立gui并连接信号槽*/;
        readState()/*更新gui数据*/;
    }


    /*values*/

    constexpr static int default_width_0x2i() { return 0; }
    constexpr static int default_step_width_0x2i() { return 1; }
    constexpr static int max_width_0x2i() { return 9999; }
    constexpr static int min_width_0x2i() { return 0; }
    int width_0x2i=default_width_0x2i();
    int step_width_0x2i=default_step_width_0x2i();
    int old_width_0x2i=default_width_0x2i();
    _0x21Q_LineEdit * edit_width_0x2i=nullptr;
    _0x21Q_LineEdit * edit_step_width_0x2i=nullptr;
    constexpr static int default_height_0x2i() { return 0; }
    constexpr static int default_step_height_0x2i() { return 1; }
    constexpr static int max_height_0x2i() { return 9999; }
    constexpr static int min_height_0x2i() { return 0; }
    int height_0x2i=default_height_0x2i();
    int step_height_0x2i=default_step_height_0x2i();
    int old_height_0x2i=default_height_0x2i();
    _0x21Q_LineEdit * edit_height_0x2i=nullptr;
    _0x21Q_LineEdit * edit_step_height_0x2i=nullptr;
    constexpr static double default_fx_0x2d() { return 0.5; }
    constexpr static double default_step_fx_0x2d() { return 0.05; }
    constexpr static double max_fx_0x2d() { return 9999; }
    constexpr static double min_fx_0x2d() { return 0; }
    double fx_0x2d=default_fx_0x2d();
    double step_fx_0x2d=default_step_fx_0x2d();
    double old_fx_0x2d=default_fx_0x2d();
    _0x21Q_LineEdit * edit_fx_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step_fx_0x2d=nullptr;
    constexpr static double default_fy_0x2d() { return 0.5; }
    constexpr static double default_step_fy_0x2d() { return 0.05; }
    constexpr static double max_fy_0x2d() { return 9999; }
    constexpr static double min_fy_0x2d() { return 0; }
    double fy_0x2d=default_fy_0x2d();
    double step_fy_0x2d=default_step_fy_0x2d();
    double old_fy_0x2d=default_fy_0x2d();
    _0x21Q_LineEdit * edit_fy_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step_fy_0x2d=nullptr;
    _0x21Q_ComboBox * enum_interpolation_0x2e=nullptr;
    int/*enum*/old_interpolation_0x2e=static_cast<int/*enum*/>(cv::INTER_NEAREST);
    int/*enum*/interpolation_0x2e=static_cast<int/*enum*/>(cv::INTER_NEAREST);
    int/*enum*/map_interpolation_0x2e(int arg) {
        switch (arg) {

            case 0: return static_cast<int/*enum*/>(cv::INTER_NEAREST);/* INTER_NEAREST */
            case 1: return static_cast<int/*enum*/>(cv::INTER_LINEAR);/* INTER_LINEAR */
            case 2: return static_cast<int/*enum*/>(cv::INTER_CUBIC);/* INTER_CUBIC */
            case 3: return static_cast<int/*enum*/>(cv::INTER_AREA);/* INTER_AREA */
            case 4: return static_cast<int/*enum*/>(cv::INTER_LANCZOS4);/* INTER_LANCZOS4 */
        }
        return static_cast<int/*enum*/>(cv::INTER_NEAREST);/*默认值*/
    }

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
            l0->setText(u8R"__(width)__" " : ");/*设置label name*/
            edit_width_0x2i=e0.pointer();
            edit_step_width_0x2i=e1.pointer();

            /*int value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_IntValidator>();
            auto && v1=makeStackPointer<_0x21Q_IntValidator>();
            v0->setRange(min_width_0x2i(),max_width_0x2i());
            v1->setRange(-9999,9999);
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_width_0x2i=e0.pointer();
            edit_step_width_0x2i=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_width_0x2i(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_width_0x2i(); });
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
            l0->setText(u8R"__(height)__" " : ");/*设置label name*/
            edit_height_0x2i=e0.pointer();
            edit_step_height_0x2i=e1.pointer();

            /*int value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_IntValidator>();
            auto && v1=makeStackPointer<_0x21Q_IntValidator>();
            v0->setRange(min_height_0x2i(),max_height_0x2i());
            v1->setRange(-9999,9999);
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_height_0x2i=e0.pointer();
            edit_step_height_0x2i=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_height_0x2i(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_height_0x2i(); });
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
            l0->setText(u8R"__(fx)__" " : ");/*设置label name*/
            edit_fx_0x2d=e0.pointer();
            edit_step_fx_0x2d=e1.pointer();

            /*double value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
            auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
            v0->setRange(min_fx_0x2d(),max_fx_0x2d());
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_fx_0x2d=e0.pointer();
            edit_step_fx_0x2d=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_fx_0x2d(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_fx_0x2d(); });
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
            l0->setText(u8R"__(fy)__" " : ");/*设置label name*/
            edit_fy_0x2d=e0.pointer();
            edit_step_fy_0x2d=e1.pointer();

            /*double value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
            auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
            v0->setRange(min_fy_0x2d(),max_fy_0x2d());
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_fy_0x2d=e0.pointer();
            edit_step_fy_0x2d=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_fy_0x2d(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_fy_0x2d(); });
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
            lvv->addLayout(l.release())/*加入主要布局*/;

            l0->setText(u8R"__(interpolation)__" " : ");/*设置label name*/

            c0->addItem(u8R"|||(INTER_NEAREST)|||");
            c0->addItem(u8R"|||(INTER_LINEAR)|||");
            c0->addItem(u8R"|||(INTER_CUBIC)|||");
            c0->addItem(u8R"|||(INTER_AREA)|||");
            c0->addItem(u8R"|||(INTER_LANCZOS4)|||");
            /*连接信号槽*/
            c0->connect(c0.pointer(),
                T_0x21Q_CurrentIndexChanged(&QComboBox::currentIndexChanged),
                super,
                [this](int) {checkDo(); });
            enum_interpolation_0x2e=c0;

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
            auto t=edit_width_0x2i->text();
            width_0x2i=t.toInt(&ok);
            if (ok) { break; }
            width_0x2i=default_width_0x2i();
            edit_width_0x2i->setText(
            QString::number(default_width_0x2i()));
        } while (false);
        do {
            auto t=edit_step_width_0x2i->text();
            step_width_0x2i=t.toInt(&ok);
            if (ok) { break; }
            step_width_0x2i=default_step_width_0x2i();
            edit_step_width_0x2i->setText(
            QString::number(default_step_width_0x2i()));
        } while (false);
        do {
            auto t=edit_height_0x2i->text();
            height_0x2i=t.toInt(&ok);
            if (ok) { break; }
            height_0x2i=default_height_0x2i();
            edit_height_0x2i->setText(
            QString::number(default_height_0x2i()));
        } while (false);
        do {
            auto t=edit_step_height_0x2i->text();
            step_height_0x2i=t.toInt(&ok);
            if (ok) { break; }
            step_height_0x2i=default_step_height_0x2i();
            edit_step_height_0x2i->setText(
            QString::number(default_step_height_0x2i()));
        } while (false);
        do {
            auto t=edit_fx_0x2d->text();
            fx_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            fx_0x2d=default_fx_0x2d();
            edit_fx_0x2d->setText(
            QString::number(default_fx_0x2d()));
        } while (false);
        do {
            auto t=edit_step_fx_0x2d->text();
            step_fx_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            step_fx_0x2d=default_step_fx_0x2d();
            edit_step_fx_0x2d->setText(
            QString::number(default_step_fx_0x2d()));
        } while (false);
        do {
            auto t=edit_fy_0x2d->text();
            fy_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            fy_0x2d=default_fy_0x2d();
            edit_fy_0x2d->setText(
            QString::number(default_fy_0x2d()));
        } while (false);
        do {
            auto t=edit_step_fy_0x2d->text();
            step_fy_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            step_fy_0x2d=default_step_fy_0x2d();
            edit_step_fy_0x2d->setText(
            QString::number(default_step_fy_0x2d()));
        } while (false);

        {interpolation_0x2e=map_interpolation_0x2e(
        enum_interpolation_0x2e->currentIndex()); }
    }
    void directDo() {
        super->valueChanged(width_0x2i
        ,height_0x2i
        ,fx_0x2d
        ,fy_0x2d
        ,interpolation_0x2e);
    }
    bool isStateChange() {
        auto ans=false;
        if (old_width_0x2i!=width_0x2i) {
            ans=true;
            old_width_0x2i=width_0x2i;
        }
        if (old_height_0x2i!=height_0x2i) {
            ans=true;
            old_height_0x2i=height_0x2i;
        }
        if (old_fx_0x2d!=fx_0x2d) {
            ans=true;
            old_fx_0x2d=fx_0x2d;
        }
        if (old_fy_0x2d!=fy_0x2d) {
            ans=true;
            old_fy_0x2d=fy_0x2d;
        }
        if (old_interpolation_0x2e!=interpolation_0x2e) {
            ans=true;
            old_interpolation_0x2e=interpolation_0x2e;
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


    void add_width_0x2i() {
        readState()/*获得当前状态*/;
        width_0x2i+=step_width_0x2i/*增加值*/;
        check_max(width_0x2i,max_width_0x2i())/*检测最大值*/;
        check_min(width_0x2i,min_width_0x2i())/*检测最小值*/;
        edit_width_0x2i->setText(
            QString::number(width_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_width_0x2i() {
        readState()/*获得当前状态*/;
        width_0x2i-=step_width_0x2i/*增加值*/;
        check_max(width_0x2i,max_width_0x2i())/*检测最大值*/;
        check_min(width_0x2i,min_width_0x2i())/*检测最小值*/;
        edit_width_0x2i->setText(
            QString::number(width_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_height_0x2i() {
        readState()/*获得当前状态*/;
        height_0x2i+=step_height_0x2i/*增加值*/;
        check_max(height_0x2i,max_height_0x2i())/*检测最大值*/;
        check_min(height_0x2i,min_height_0x2i())/*检测最小值*/;
        edit_height_0x2i->setText(
            QString::number(height_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_height_0x2i() {
        readState()/*获得当前状态*/;
        height_0x2i-=step_height_0x2i/*增加值*/;
        check_max(height_0x2i,max_height_0x2i())/*检测最大值*/;
        check_min(height_0x2i,min_height_0x2i())/*检测最小值*/;
        edit_height_0x2i->setText(
            QString::number(height_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_fx_0x2d() {
        readState()/*获得当前状态*/;
        fx_0x2d+=step_fx_0x2d/*增加值*/;
        check_max(fx_0x2d,max_fx_0x2d())/*检测最大值*/;
        check_min(fx_0x2d,min_fx_0x2d())/*检测最小值*/;
        edit_fx_0x2d->setText(
            QString::number(fx_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_fx_0x2d() {
        readState()/*获得当前状态*/;
        fx_0x2d-=step_fx_0x2d/*增加值*/;
        check_max(fx_0x2d,max_fx_0x2d())/*检测最大值*/;
        check_min(fx_0x2d,min_fx_0x2d())/*检测最小值*/;
        edit_fx_0x2d->setText(
            QString::number(fx_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_fy_0x2d() {
        readState()/*获得当前状态*/;
        fy_0x2d+=step_fy_0x2d/*增加值*/;
        check_max(fy_0x2d,max_fy_0x2d())/*检测最大值*/;
        check_min(fy_0x2d,min_fy_0x2d())/*检测最小值*/;
        edit_fy_0x2d->setText(
            QString::number(fy_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_fy_0x2d() {
        readState()/*获得当前状态*/;
        fy_0x2d-=step_fy_0x2d/*增加值*/;
        check_max(fy_0x2d,max_fy_0x2d())/*检测最大值*/;
        check_min(fy_0x2d,min_fy_0x2d())/*检测最小值*/;
        edit_fy_0x2d->setText(
            QString::number(fy_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }


private:
    CPLUSPLUS_OBJECT(_PrivateResizeDialog)
};

ResizeDialog::ResizeDialog(QWidget *p):_Super(p) {
    thisp=new _PrivateResizeDialog(this);
}

ResizeDialog::~ResizeDialog() {
    delete thisp;
}

void ResizeDialog::emitValueChanged() {
    thisp->readState();
    thisp->directDo();
}

QSize ResizeDialog::sizeHint() const {
    return{ 136,128 };
}

QVBoxLayout * ResizeDialog::getMainLayout() const {
    return thisp->mainLayout;
}

/*End of the file.*/


