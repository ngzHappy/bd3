#include "CopyMakeBorderDialog.hpp"
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

class CopyMakeBorderDialog::_PrivateCopyMakeBorderDialog{
public:
    CopyMakeBorderDialog *super;
    _PrivateCopyMakeBorderDialog(CopyMakeBorderDialog *arg):super(arg){
        setup_ui()/*建立gui并连接信号槽*/;
        readState()/*更新gui数据*/;
    }


    /*values*/

    constexpr static int default_top_0x2i(){return 5;}
    constexpr static int default_step_top_0x2i(){return 1;}
    constexpr static int max_top_0x2i(){return 9999;}
    constexpr static int min_top_0x2i(){return 0;}
    int top_0x2i=default_top_0x2i();
    int step_top_0x2i=default_step_top_0x2i();
    int old_top_0x2i=default_top_0x2i();
    _0x21Q_LineEdit * edit_top_0x2i=nullptr;
    _0x21Q_LineEdit * edit_step_top_0x2i=nullptr;
    constexpr static int default_bottom_0x2i(){return 5;}
    constexpr static int default_step_bottom_0x2i(){return 1;}
    constexpr static int max_bottom_0x2i(){return 9999;}
    constexpr static int min_bottom_0x2i(){return 0;}
    int bottom_0x2i=default_bottom_0x2i();
    int step_bottom_0x2i=default_step_bottom_0x2i();
    int old_bottom_0x2i=default_bottom_0x2i();
    _0x21Q_LineEdit * edit_bottom_0x2i=nullptr;
    _0x21Q_LineEdit * edit_step_bottom_0x2i=nullptr;
    constexpr static int default_left_0x2i(){return 5;}
    constexpr static int default_step_left_0x2i(){return 1;}
    constexpr static int max_left_0x2i(){return 9999;}
    constexpr static int min_left_0x2i(){return 0;}
    int left_0x2i=default_left_0x2i();
    int step_left_0x2i=default_step_left_0x2i();
    int old_left_0x2i=default_left_0x2i();
    _0x21Q_LineEdit * edit_left_0x2i=nullptr;
    _0x21Q_LineEdit * edit_step_left_0x2i=nullptr;
    constexpr static int default_right_0x2i(){return 5;}
    constexpr static int default_step_right_0x2i(){return 1;}
    constexpr static int max_right_0x2i(){return 0;}
    constexpr static int min_right_0x2i(){return 0;}
    int right_0x2i=default_right_0x2i();
    int step_right_0x2i=default_step_right_0x2i();
    int old_right_0x2i=default_right_0x2i();
    _0x21Q_LineEdit * edit_right_0x2i=nullptr;
    _0x21Q_LineEdit * edit_step_right_0x2i=nullptr;
    _0x21Q_ComboBox * enum_borderType_0x2e=nullptr;
    int/*enum*/old_borderType_0x2e=static_cast<int/*enum*/>( cv::BORDER_CONSTANT );
    int/*enum*/borderType_0x2e=static_cast<int/*enum*/>( cv::BORDER_CONSTANT );
    int/*enum*/map_borderType_0x2e(int arg) {
        switch(arg){

        case 0 : return static_cast<int/*enum*/>( cv::BORDER_CONSTANT );/* BORDER_CONSTANT */
        case 1 : return static_cast<int/*enum*/>( cv::BORDER_REPLICATE );/* BORDER_REPLICATE */
        case 2 : return static_cast<int/*enum*/>( cv::BORDER_REFLECT );/* BORDER_REFLECT */
        case 3 : return static_cast<int/*enum*/>( cv::BORDER_WRAP );/* BORDER_WRAP */
        case 4 : return static_cast<int/*enum*/>( cv::BORDER_REFLECT_101 );/* BORDER_REFLECT_101 */
        case 5 : return static_cast<int/*enum*/>( cv::BORDER_TRANSPARENT );/* BORDER_TRANSPARENT */
        }
        return static_cast<int/*enum*/>( cv::BORDER_CONSTANT );/*默认值*/
    }

    void setup_ui(){
        using namespace memory ;
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
            l0->setText(u8R"__(top)__" " : " );/*设置label name*/
            edit_top_0x2i=e0.pointer();
            edit_step_top_0x2i=e1.pointer();

            /*int value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_IntValidator>();
            auto && v1=makeStackPointer<_0x21Q_IntValidator>();
            v0->setRange(min_top_0x2i(),max_top_0x2i());
            v1->setRange(-9999,9999);
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_top_0x2i=e0.pointer();
            edit_step_top_0x2i=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
                                 /*连接信号槽*/super,[this](bool) {add_top_0x2i(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
                                 /*连接信号槽*/super,[this](bool) {sub_top_0x2i(); });
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
            l0->setText(u8R"__(bottom)__" " : " );/*设置label name*/
            edit_bottom_0x2i=e0.pointer();
            edit_step_bottom_0x2i=e1.pointer();

            /*int value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_IntValidator>();
            auto && v1=makeStackPointer<_0x21Q_IntValidator>();
            v0->setRange(min_bottom_0x2i(),max_bottom_0x2i());
            v1->setRange(-9999,9999);
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_bottom_0x2i=e0.pointer();
            edit_step_bottom_0x2i=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
                                 /*连接信号槽*/super,[this](bool) {add_bottom_0x2i(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
                                 /*连接信号槽*/super,[this](bool) {sub_bottom_0x2i(); });
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
            l0->setText(u8R"__(left)__" " : " );/*设置label name*/
            edit_left_0x2i=e0.pointer();
            edit_step_left_0x2i=e1.pointer();

            /*int value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_IntValidator>();
            auto && v1=makeStackPointer<_0x21Q_IntValidator>();
            v0->setRange(min_left_0x2i(),max_left_0x2i());
            v1->setRange(-9999,9999);
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_left_0x2i=e0.pointer();
            edit_step_left_0x2i=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
                                 /*连接信号槽*/super,[this](bool) {add_left_0x2i(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
                                 /*连接信号槽*/super,[this](bool) {sub_left_0x2i(); });
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
            l0->setText(u8R"__(right)__" " : " );/*设置label name*/
            edit_right_0x2i=e0.pointer();
            edit_step_right_0x2i=e1.pointer();

            /*int value 检查器*/
            auto && v0=makeStackPointer<_0x21Q_IntValidator>();
            auto && v1=makeStackPointer<_0x21Q_IntValidator>();
            v0->setRange(min_right_0x2i(),max_right_0x2i());
            v1->setRange(-9999,9999);
            v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
            edit_right_0x2i=e0.pointer();
            edit_step_right_0x2i=e1.pointer();

            /*连接信号槽*/
            /*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
                                 /*连接信号槽*/super,[this](bool) {add_right_0x2i(); });
            /*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
                                 /*连接信号槽*/super,[this](bool) {sub_right_0x2i(); });
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

            l0->setText(u8R"__(borderType)__" " : " );/*设置label name*/

            c0->addItem( u8R"|||(BORDER_CONSTANT)|||" );
            c0->addItem( u8R"|||(BORDER_REPLICATE)|||" );
            c0->addItem( u8R"|||(BORDER_REFLECT)|||" );
            c0->addItem( u8R"|||(BORDER_WRAP)|||" );
            c0->addItem( u8R"|||(BORDER_REFLECT_101)|||" );
            c0->addItem( u8R"|||(BORDER_TRANSPARENT)|||" );
            /*连接信号槽*/
            c0->connect(c0.pointer(),
                        T_0x21Q_CurrentIndexChanged(&QComboBox::currentIndexChanged),
                        super,
                        [this](int) {checkDo(); });
            enum_borderType_0x2e=c0;

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
            auto t=edit_top_0x2i->text();
            top_0x2i= t.toInt(&ok);
            if (ok) { break; }
            top_0x2i=default_top_0x2i();
            edit_top_0x2i->setText(
                        QString::number(default_top_0x2i()));
        } while (false);
        do{
            auto t=edit_step_top_0x2i->text();
            step_top_0x2i= t.toInt(&ok);
            if (ok) { break; }
            step_top_0x2i=default_step_top_0x2i();
            edit_step_top_0x2i->setText(
                        QString::number(default_step_top_0x2i()));
        } while (false);
        do{
            auto t=edit_bottom_0x2i->text();
            bottom_0x2i= t.toInt(&ok);
            if (ok) { break; }
            bottom_0x2i=default_bottom_0x2i();
            edit_bottom_0x2i->setText(
                        QString::number(default_bottom_0x2i()));
        } while (false);
        do{
            auto t=edit_step_bottom_0x2i->text();
            step_bottom_0x2i= t.toInt(&ok);
            if (ok) { break; }
            step_bottom_0x2i=default_step_bottom_0x2i();
            edit_step_bottom_0x2i->setText(
                        QString::number(default_step_bottom_0x2i()));
        } while (false);
        do{
            auto t=edit_left_0x2i->text();
            left_0x2i= t.toInt(&ok);
            if (ok) { break; }
            left_0x2i=default_left_0x2i();
            edit_left_0x2i->setText(
                        QString::number(default_left_0x2i()));
        } while (false);
        do{
            auto t=edit_step_left_0x2i->text();
            step_left_0x2i= t.toInt(&ok);
            if (ok) { break; }
            step_left_0x2i=default_step_left_0x2i();
            edit_step_left_0x2i->setText(
                        QString::number(default_step_left_0x2i()));
        } while (false);
        do{
            auto t=edit_right_0x2i->text();
            right_0x2i= t.toInt(&ok);
            if (ok) { break; }
            right_0x2i=default_right_0x2i();
            edit_right_0x2i->setText(
                        QString::number(default_right_0x2i()));
        } while (false);
        do{
            auto t=edit_step_right_0x2i->text();
            step_right_0x2i= t.toInt(&ok);
            if (ok) { break; }
            step_right_0x2i=default_step_right_0x2i();
            edit_step_right_0x2i->setText(
                        QString::number(default_step_right_0x2i()));
        } while (false);

        {borderType_0x2e=map_borderType_0x2e(
                        enum_borderType_0x2e->currentIndex());}
    }
    void directDo() {
        super->valueChanged(top_0x2i
                            ,bottom_0x2i
                            ,left_0x2i
                            ,right_0x2i
                            ,borderType_0x2e);
    }
    bool isStateChange() {
        auto ans=false;
        if (old_top_0x2i!=top_0x2i){
            ans=true;
            old_top_0x2i=top_0x2i;
        }
        if (old_bottom_0x2i!=bottom_0x2i){
            ans=true;
            old_bottom_0x2i=bottom_0x2i;
        }
        if (old_left_0x2i!=left_0x2i){
            ans=true;
            old_left_0x2i=left_0x2i;
        }
        if (old_right_0x2i!=right_0x2i){
            ans=true;
            old_right_0x2i=right_0x2i;
        }
        if (old_borderType_0x2e!=borderType_0x2e){
            ans=true;
            old_borderType_0x2e=borderType_0x2e;
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


    void add_top_0x2i() {
        readState()/*获得当前状态*/;
        top_0x2i+=step_top_0x2i/*增加值*/;
        check_max(top_0x2i,max_top_0x2i())/*检测最大值*/;
        check_min(top_0x2i,min_top_0x2i())/*检测最小值*/;
        edit_top_0x2i->setText(
                    QString::number(top_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_top_0x2i() {
        readState()/*获得当前状态*/;
        top_0x2i-=step_top_0x2i/*增加值*/;
        check_max(top_0x2i,max_top_0x2i())/*检测最大值*/;
        check_min(top_0x2i,min_top_0x2i())/*检测最小值*/;
        edit_top_0x2i->setText(
                    QString::number(top_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_bottom_0x2i() {
        readState()/*获得当前状态*/;
        bottom_0x2i+=step_bottom_0x2i/*增加值*/;
        check_max(bottom_0x2i,max_bottom_0x2i())/*检测最大值*/;
        check_min(bottom_0x2i,min_bottom_0x2i())/*检测最小值*/;
        edit_bottom_0x2i->setText(
                    QString::number(bottom_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_bottom_0x2i() {
        readState()/*获得当前状态*/;
        bottom_0x2i-=step_bottom_0x2i/*增加值*/;
        check_max(bottom_0x2i,max_bottom_0x2i())/*检测最大值*/;
        check_min(bottom_0x2i,min_bottom_0x2i())/*检测最小值*/;
        edit_bottom_0x2i->setText(
                    QString::number(bottom_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_left_0x2i() {
        readState()/*获得当前状态*/;
        left_0x2i+=step_left_0x2i/*增加值*/;
        check_max(left_0x2i,max_left_0x2i())/*检测最大值*/;
        check_min(left_0x2i,min_left_0x2i())/*检测最小值*/;
        edit_left_0x2i->setText(
                    QString::number(left_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_left_0x2i() {
        readState()/*获得当前状态*/;
        left_0x2i-=step_left_0x2i/*增加值*/;
        check_max(left_0x2i,max_left_0x2i())/*检测最大值*/;
        check_min(left_0x2i,min_left_0x2i())/*检测最小值*/;
        edit_left_0x2i->setText(
                    QString::number(left_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void add_right_0x2i() {
        readState()/*获得当前状态*/;
        right_0x2i+=step_right_0x2i/*增加值*/;
        check_max(right_0x2i,max_right_0x2i())/*检测最大值*/;
        check_min(right_0x2i,min_right_0x2i())/*检测最小值*/;
        edit_right_0x2i->setText(
                    QString::number(right_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }

    void sub_right_0x2i() {
        readState()/*获得当前状态*/;
        right_0x2i-=step_right_0x2i/*增加值*/;
        check_max(right_0x2i,max_right_0x2i())/*检测最大值*/;
        check_min(right_0x2i,min_right_0x2i())/*检测最小值*/;
        edit_right_0x2i->setText(
                    QString::number(right_0x2i))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }


private:
    CPLUSPLUS_OBJECT(_PrivateCopyMakeBorderDialog)
};

CopyMakeBorderDialog::CopyMakeBorderDialog(QWidget *p):_Super(p){
    thisp=new _PrivateCopyMakeBorderDialog(this);
}

CopyMakeBorderDialog::~CopyMakeBorderDialog(){
    delete thisp;
}

void CopyMakeBorderDialog::emitValueChanged() {
    thisp->directDo();
}

QSize CopyMakeBorderDialog::sizeHint() const {
    return {136,128};
}

/*End of the file.*/


