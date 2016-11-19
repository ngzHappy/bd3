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
    _PrivateXDialog(XDialog *arg):super(arg){
        setup_ui();
    }


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
        auto && lv=makeStackPointer<_0x21Q_VBoxLayout>();
        super->setLayout(lv.release());
        lv->setSpacing(0);
        lv->setMargin(0);

        {
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
        } 
        {
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
        } 

        {
            auto && ls=makeStackPointer<_0x21Q_SpacerItem>(
                1,1,QSizePolicy::Minimum,
                QSizePolicy::MinimumExpanding
                );
            lv->addSpacerItem(ls.release());
        }

        {
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
        }
    }/*function end*/


private:
    CPLUSPLUS_OBJECT(_PrivateXDialog)
};

XDialog::XDialog(QWidget *p):_Super(p){
    thisp=new _PrivateXDialog(this);
}

XDialog::~XDialog(){
    delete thisp;
}


