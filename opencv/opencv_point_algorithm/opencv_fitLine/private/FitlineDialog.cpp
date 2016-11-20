#include "FitlineDialog.hpp"
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

class FitlineDialog::_PrivateFitlineDialog {
public:
    FitlineDialog *super;
    _PrivateFitlineDialog(FitlineDialog *arg):super(arg) {
        setup_ui()/*建立gui并连接信号槽*/;
        readState()/*更新gui数据*/;
    }


    /*values*/

    _0x21Q_ComboBox * enum_distType_0x2e=nullptr;
    int/*enum*/old_distType_0x2e=static_cast<int/*enum*/>(cv::DIST_L2);
    int/*enum*/distType_0x2e=static_cast<int/*enum*/>(cv::DIST_L2);
    int/*enum*/map_distType_0x2e(int arg) {
        switch (arg) {

            case 0: return static_cast<int/*enum*/>(cv::DIST_L2);/* DIST_L2 */
            case 1: return static_cast<int/*enum*/>(cv::DIST_L1);/* DIST_L1 */
            case 2: return static_cast<int/*enum*/>(cv::DIST_FAIR);/* DIST_FAIR */
            case 3: return static_cast<int/*enum*/>(cv::DIST_WELSCH);/* DIST_WELSCH */
            case 4: return static_cast<int/*enum*/>(cv::DIST_HUBER);/* DIST_HUBER */
        }
        return static_cast<int/*enum*/>(cv::DIST_L2);/*默认值*/
    }

    constexpr static double default_param_0x2d() { return 0; }
    constexpr static double default_step_param_0x2d() { return 0.05; }
    constexpr static double max_param_0x2d() { return 9999; }
    constexpr static double min_param_0x2d() { return -9999; }
    double param_0x2d=default_param_0x2d();
    double step_param_0x2d=default_step_param_0x2d();
    double old_param_0x2d=default_param_0x2d();
    _0x21Q_LineEdit * edit_param_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step_param_0x2d=nullptr;
    constexpr static double default_reps_0x2d() { return 0.01; }
    constexpr static double default_step_reps_0x2d() { return 0.05; }
    constexpr static double max_reps_0x2d() { return 9999; }
    constexpr static double min_reps_0x2d() { return -9999; }
    double reps_0x2d=default_reps_0x2d();
    double step_reps_0x2d=default_step_reps_0x2d();
    double old_reps_0x2d=default_reps_0x2d();
    _0x21Q_LineEdit * edit_reps_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step_reps_0x2d=nullptr;
    constexpr static double default_aeps_0x2d() { return 0.01; }
    constexpr static double default_step_aeps_0x2d() { return 0.05; }
    constexpr static double max_aeps_0x2d() { return 9999; }
    constexpr static double min_aeps_0x2d() { return -9999; }
    double aeps_0x2d=default_aeps_0x2d();
    double step_aeps_0x2d=default_step_aeps_0x2d();
    double old_aeps_0x2d=default_aeps_0x2d();
    _0x21Q_LineEdit * edit_aeps_0x2d=nullptr;
    _0x21Q_LineEdit * edit_step_aeps_0x2d=nullptr;
    void setup_ui() {
        using namespace memory;
        /*窗口布局*/
        auto && lv=makeStackPointer<_0x21Q_VBoxLayout>();
        super->setLayout(lv.release());
        lv->setSpacing(0);
        lv->setMargin(0);

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

            l0->setText(u8R"__(distType)__" " : ");/*设置label name*/

            c0->addItem(u8R"|||(DIST_L2)|||");
            c0->addItem(u8R"|||(DIST_L1)|||");
            c0->addItem(u8R"|||(DIST_FAIR)|||");
            c0->addItem(u8R"|||(DIST_WELSCH)|||");
            c0->addItem(u8R"|||(DIST_HUBER)|||");
            /*连接信号槽*/
            c0->connect(c0.pointer(),
                T_0x21Q_CurrentIndexChanged(&QComboBox::currentIndexChanged),
                super,
                [this](int) {checkDo(); });
            enum_distType_0x2e=c0;

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
            l0->setText(u8R"__(param)__" " : ");/*设置label name*/
            edit_param_0x2d=e0.pointer();
            edit_step_param_0x2d=e1.pointer();

            /*double value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
            auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
            v0->setRange(min_param_0x2d(),max_param_0x2d());
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_param_0x2d=e0.pointer();
            edit_step_param_0x2d=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_param_0x2d(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_param_0x2d(); });
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
            l0->setText(u8R"__(reps)__" " : ");/*设置label name*/
            edit_reps_0x2d=e0.pointer();
            edit_step_reps_0x2d=e1.pointer();

            /*double value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
            auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
            v0->setRange(min_reps_0x2d(),max_reps_0x2d());
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_reps_0x2d=e0.pointer();
            edit_step_reps_0x2d=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_reps_0x2d(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_reps_0x2d(); });
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
            l0->setText(u8R"__(aeps)__" " : ");/*设置label name*/
            edit_aeps_0x2d=e0.pointer();
            edit_step_aeps_0x2d=e1.pointer();

            /*double value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
            auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
            v0->setRange(min_aeps_0x2d(),max_aeps_0x2d());
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_aeps_0x2d=e0.pointer();
            edit_step_aeps_0x2d=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {add_aeps_0x2d(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
            /*连接信号槽*/super,[this](bool) {sub_aeps_0x2d(); });
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

        {distType_0x2e=map_distType_0x2e(
        enum_distType_0x2e->currentIndex()); }
        do {
            auto t=edit_param_0x2d->text();
            param_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            param_0x2d=default_param_0x2d();
            edit_param_0x2d->setText(
            QString::number(default_param_0x2d()));
        } while (false);
        do {
            auto t=edit_step_param_0x2d->text();
            step_param_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            step_param_0x2d=default_step_param_0x2d();
            edit_step_param_0x2d->setText(
            QString::number(default_step_param_0x2d()));
        } while (false);
        do {
            auto t=edit_reps_0x2d->text();
            reps_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            reps_0x2d=default_reps_0x2d();
            edit_reps_0x2d->setText(
            QString::number(default_reps_0x2d()));
        } while (false);
        do {
            auto t=edit_step_reps_0x2d->text();
            step_reps_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            step_reps_0x2d=default_step_reps_0x2d();
            edit_step_reps_0x2d->setText(
            QString::number(default_step_reps_0x2d()));
        } while (false);
        do {
            auto t=edit_aeps_0x2d->text();
            aeps_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            aeps_0x2d=default_aeps_0x2d();
            edit_aeps_0x2d->setText(
            QString::number(default_aeps_0x2d()));
        } while (false);
        do {
            auto t=edit_step_aeps_0x2d->text();
            step_aeps_0x2d=t.toDouble(&ok);
            if (ok) { break; }
            step_aeps_0x2d=default_step_aeps_0x2d();
            edit_step_aeps_0x2d->setText(
            QString::number(default_step_aeps_0x2d()));
        } while (false);
    }
    void directDo() {
        super->valueChanged(distType_0x2e
        ,param_0x2d
        ,reps_0x2d
        ,aeps_0x2d);
    }
    bool isStateChange() {
        auto ans=false;
        if (old_distType_0x2e!=distType_0x2e) {
            ans=true;
            old_distType_0x2e=distType_0x2e;
        }
        if (old_param_0x2d!=param_0x2d) {
            ans=true;
            old_param_0x2d=param_0x2d;
        }
        if (old_reps_0x2d!=reps_0x2d) {
            ans=true;
            old_reps_0x2d=reps_0x2d;
        }
        if (old_aeps_0x2d!=aeps_0x2d) {
            ans=true;
            old_aeps_0x2d=aeps_0x2d;
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


    void add_param_0x2d() {
        readState()/*获得当前状态*/;
        param_0x2d+=step_param_0x2d/*增加值*/;
        check_max(param_0x2d,max_param_0x2d())/*检测最大值*/;
        check_min(param_0x2d,min_param_0x2d())/*检测最小值*/;
        edit_param_0x2d->setText(
            QString::number(param_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_param_0x2d() {
        readState()/*获得当前状态*/;
        param_0x2d-=step_param_0x2d/*增加值*/;
        check_max(param_0x2d,max_param_0x2d())/*检测最大值*/;
        check_min(param_0x2d,min_param_0x2d())/*检测最小值*/;
        edit_param_0x2d->setText(
            QString::number(param_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_reps_0x2d() {
        readState()/*获得当前状态*/;
        reps_0x2d+=step_reps_0x2d/*增加值*/;
        check_max(reps_0x2d,max_reps_0x2d())/*检测最大值*/;
        check_min(reps_0x2d,min_reps_0x2d())/*检测最小值*/;
        edit_reps_0x2d->setText(
            QString::number(reps_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_reps_0x2d() {
        readState()/*获得当前状态*/;
        reps_0x2d-=step_reps_0x2d/*增加值*/;
        check_max(reps_0x2d,max_reps_0x2d())/*检测最大值*/;
        check_min(reps_0x2d,min_reps_0x2d())/*检测最小值*/;
        edit_reps_0x2d->setText(
            QString::number(reps_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_aeps_0x2d() {
        readState()/*获得当前状态*/;
        aeps_0x2d+=step_aeps_0x2d/*增加值*/;
        check_max(aeps_0x2d,max_aeps_0x2d())/*检测最大值*/;
        check_min(aeps_0x2d,min_aeps_0x2d())/*检测最小值*/;
        edit_aeps_0x2d->setText(
            QString::number(aeps_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_aeps_0x2d() {
        readState()/*获得当前状态*/;
        aeps_0x2d-=step_aeps_0x2d/*增加值*/;
        check_max(aeps_0x2d,max_aeps_0x2d())/*检测最大值*/;
        check_min(aeps_0x2d,min_aeps_0x2d())/*检测最小值*/;
        edit_aeps_0x2d->setText(
            QString::number(aeps_0x2d))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }


private:
    CPLUSPLUS_OBJECT(_PrivateFitlineDialog)
};

FitlineDialog::FitlineDialog(QWidget *p):_Super(p) {
    thisp=new _PrivateFitlineDialog(this);
}

FitlineDialog::~FitlineDialog() {
    delete thisp;
}

void FitlineDialog::emitValueChanged() {
    thisp->directDo();
}

QSize FitlineDialog::sizeHint() const {
    return{ 136,128 };
}

/*End of the file.*/


