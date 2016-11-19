﻿#include <QtCore>
#include <QtWidgets>
#include <vector>
#include <cstring>
#include <regex>
#include <lua/lua.hpp>
#include <text/to_plain_text.hpp>
#include "MainWindow.hpp"

namespace {

template<typename T>
using vector=std::vector<T,memory::Allocator<T>>;
using string=std::basic_string<char,
    std::char_traits<char>,memory::Allocator<char> >;

}

class MainWindow::_PrivateMainWindow {
public:
    QLineEdit * luaFilePath;
    QLineEdit * outDir;

private:
    string luaFileData;
    string className;

    lua::State *L;

    enum Type {
        t_unknow,
        t_int,t_double
    };

    class Value {
    public:
        virtual ~Value() {}
        virtual const string & unique_name()const=0;
        virtual Type type() const { return t_unknow; }
    };
    vector<std::unique_ptr<const Value>> values;

    class IntValue :public Value {
    public:
        int default_value;
        int max_value;
        int min_value;
        int step_default;
        string name;
        string u_name;
        void setName(string _name) {
            name=std::move(_name);
            const static std::regex rg("X");
            u_name=std::regex_replace(name,rg,"_x_");
            u_name+="_0x2i";
        }
        Type type() const override { return t_int; }
        const string & unique_name()const override { return u_name; }
    private:
        CPLUSPLUS_OBJECT(IntValue)
    };
    class DoubleValue :public Value {
    public:
        double default_value;
        double max_value;
        double min_value;
        double step_default;
        string name;
        string u_name;
        void setName(string _name) {
            name=std::move(_name);
            const static std::regex rg("X");
            u_name=std::regex_replace(name,rg,"_x_");
            u_name+="_0x2d";
        }
        Type type() const override { return t_double; }
        const string & unique_name()const override { return u_name; }
    private:
        CPLUSPLUS_OBJECT(DoubleValue)
    };

    void readLuaFileData() {
        QFile file(luaFilePath->text());

        luaFileData.clear();
        className.clear();
        values.clear();

        QByteArray data;
        if (file.open(QIODevice::ReadOnly)) {
            data=file.readAll();
        }
        if (data.isEmpty()) { return; }
        auto ans=text::to_plain_text(data.begin(),data.end());
        luaFileData=string(ans.begin(),ans.end());
    }

    class StateUpdateDataFromLua {
    public:
        _PrivateMainWindow *super;
    };
    template<size_t N>
    static bool str_cmp(
        const char *arg,size_t l,
        const char(&arg1)[N]
    ) {
        if (l==(N-1)) {
            return 0==std::strncmp(arg,arg1,(N-1));
        }return false;
    }
    static void readDateFromLua_(lua::State *L,
        StateUpdateDataFromLua * state) {

        auto & values=state->super->values;

        if (lua::istable(L,-1)==false) {
            return;
        }

        auto tablePos=lua::gettop(L);
        auto keypos=tablePos+1;
        auto valuePos=tablePos+2;
        lua::pushnil(L);

        size_t strl;
        while (lua::next(L,tablePos)) {

            if (lua::isinteger(L,keypos)) {
                const char * skey;
                string key;
                if (lua::istable(L,valuePos)) {
                    lua::rawgeti(L,valuePos,1);
                    if (lua::isstring(L,-1)) {
                        skey=lua::tolstring(L,-1,&strl);
                        if (str_cmp(skey,strl,"int_value")) {
                            auto && value=memory::makeStackPointer<IntValue>();
                            lua::rawgeti(L,valuePos,2);
                            skey=lua::tolstring(L,-1,&strl);
                            key.assign(skey,strl);
                            value->setName(std::move(key));
                            lua::rawgeti(L,valuePos,3);
                            value->default_value=lua::tointeger(L,-1);
                            lua::rawgeti(L,valuePos,4);
                            value->min_value=lua::tointeger(L,-1);
                            lua::rawgeti(L,valuePos,5);
                            value->max_value=lua::tointeger(L,-1);
                            lua::rawgeti(L,valuePos,6);
                            value->step_default=lua::tointeger(L,-1);
                            values.push_back(value.toConstStdPointer());
                        }
                        else if (str_cmp(skey,strl,"double_value")) {
                            auto && value=memory::makeStackPointer<DoubleValue>();
                            lua::rawgeti(L,valuePos,2);
                            skey=lua::tolstring(L,-1,&strl);
                            key.assign(skey,strl);
                            value->setName(std::move(key));
                            lua::rawgeti(L,valuePos,3);
                            value->default_value=lua::tonumber(L,-1);
                            lua::rawgeti(L,valuePos,4);
                            value->min_value=lua::tonumber(L,-1);
                            lua::rawgeti(L,valuePos,5);
                            value->max_value=lua::tonumber(L,-1);
                            lua::rawgeti(L,valuePos,6);
                            value->step_default=lua::tonumber(L,-1);
                            values.push_back(value.toConstStdPointer());
                        }
                    }
                }
            }

            lua::settop(L,keypos);
        }


    }
    static int updateDataFromLua(lua::State *L) {
        lua::checkstack(L,100);
        auto state=
            reinterpret_cast<StateUpdateDataFromLua*>(
                lua::touserdata(L,-1));
        const auto &luaFileData=
            state->super->luaFileData;

        if (lua::OK==luaL::loadstring(L,luaFileData.c_str())) {
            if (lua::OK==lua::pcall(L,0,LUA_MULTRET,0)) {
                if (lua::istable(L,-1)) {

                    auto tablePos=lua::gettop(L);
                    auto keyPos=tablePos+1;
                    auto valuePos=tablePos+2;
                    lua::pushnil(L);

                    size_t strSize;
                    while (lua::next(L,tablePos)) {
                        if (lua::isstring(L,keyPos)) {
                            auto str=lua::tolstring(L,keyPos,&strSize);
                            if ((strSize==4)&&(std::strncmp(str,"name",4)==0)) {
                                str=lua::tolstring(L,valuePos,&strSize);
                                state->super->className.assign(str,strSize);
                            }
                            else if ((strSize==6)&&(std::strncmp(str,"values",6)==0)) {
                                readDateFromLua_(L,state);
                            }
                        }
                        lua::settop(L,keyPos);
                    }

                }
            }
        }
        else {
            luaL::default_error_function(L);
            return 0;
        }
        return 0;
    }

public:
    ~_PrivateMainWindow() {
        lua::close(L);
    }
    _PrivateMainWindow() {
        L=luaL::newstate();
        lua::openlibs(L);
        lua::checkstack(L,1024);
    }

    void writeHpp() {
        QFile file(outDir->text()+"/"+className.c_str()+".hpp");
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            stream<<bom;

            const QString varClassName=QString::fromUtf8(className.c_str(),
              static_cast<int> (className.size()));

            stream<<QLatin1Literal("#ifndef __HPP_");
            stream<<varClassName.toUpper();
            stream<<"0x21003";
            stream<<endl;

            stream<<QLatin1Literal("#define __HPP_");
            stream<<varClassName.toUpper();
            stream<<"0x21003";
            stream<<endl;

            QString data=QString::fromUtf8(u8R"(

#include <cplusplus_basic.hpp>
#include <QtWidgets/qwidget.h>

class XDialog : public QWidget
{
    Q_OBJECT

private:
    using _Super=QWidget;
    class _PrivateXDialog;
    _PrivateXDialog *thisp=nullptr;
public:
    explicit XDialog(QWidget * /**/=nullptr);
    virtual ~XDialog();
public:
    //Q_SIGNAL_valueChanged__;
private:
    XDialog(const XDialog&)=delete;
    XDialog(XDialog&&)=delete;
    XDialog&operator=(const XDialog&)=delete;
    XDialog&operator=(XDialog&&)=delete;
private:
    CPLUSPLUS_OBJECT(XDialog)
};

 )");
            data.replace("XDialog",varClassName);
            {
                QString varSignal("Q_SIGNAL void valueChanged(");
                bool isFirst=true;
                for (const auto &i:values) {
                    if (false==isFirst) {
                        varSignal+=" , ";
                    }
                    switch (i->type()) {
                        case t_int: {
                            auto j=static_cast<const IntValue*>(i.get());
                            varSignal+="int /* ";
                            varSignal+=j->name.c_str();
                            varSignal+=" */";
                        }break;
                        case t_double: {
                            auto j=static_cast<const DoubleValue*>(i.get());
                            varSignal+="double /* ";
                            varSignal+=j->name.c_str();
                            varSignal+=" */";
                        }break;
                    }
                    isFirst=false;
                }
                varSignal+=");";
                data.replace("//Q_SIGNAL_valueChanged__;",varSignal);
            }
            stream<<data;

            stream<<"#endif /**/";
            stream<<endl;
            stream<<endl;
        }
    }

    void writeCpp() {

        QFile file(outDir->text()+"/"+className.c_str()+".cpp");
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            stream<<bom;

            const QString varClassName=QString::fromUtf8(className.c_str(),
                static_cast<int> (className.size()));

            QString data;
            data+=u8R"~(#include "XDialog.hpp"
#include <QtWidgets/qlabel.h>
#include <QtGui/qvalidator.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtoolbutton.h>
#include <QtWidgets/qlayoutitem.h>

namespace  {

class _0x21Q_DoubleValidator :public QDoubleValidator {
    using _Super=QDoubleValidator;
public:
    using _Super::_Super;
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

class XDialog::_PrivateXDialog{
public:
    XDialog *super;
    _PrivateXDialog(XDialog *arg):super(arg){
 setup_ui();
}

)~";

            data+=u8R"(
/*values*/
)";

            for (const auto &i:values) {
                if (i->type()==t_int) {

                    auto j=static_cast<const IntValue *>(i.get());
                    data+=u8R"(
constexpr static int default_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"((){return )";
                    data+=QString::number(j->default_value);
                    data+=u8R"(;})";

                    data+=u8R"(
constexpr static int default_step_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"((){return )";
                    data+=QString::number(j->step_default);
                    data+=u8R"(;})";

                    data+=u8R"(
constexpr static int max_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"((){return )";
                    data+=QString::number(j->max_value);
                    data+=u8R"(;})";

                    data+=u8R"(
constexpr static int min_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"((){return )";
                    data+=QString::number(j->min_value);
                    data+=u8R"(;})";
                    ///////////////////
                    data+=u8R"(
int )";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=default_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(();)";

                    data+=u8R"(
int step_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=default_step_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(();)";

                    data+=u8R"(
int old_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=default_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(();)";

                    data+=u8R"(
_0x21Q_LineEdit * edit_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=nullptr;)";

                    data+=u8R"(
_0x21Q_LineEdit * edit_step_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=nullptr;)";

                }
                else if (i->type()==t_double) {
                    auto j=static_cast<const DoubleValue *>(i.get());
                    data+=u8R"(
constexpr static double default_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"((){return )";
                    data+=QString::number(j->default_value);
                    data+=u8R"(;})";

                    data+=u8R"(
constexpr static double default_step_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"((){return )";
                    data+=QString::number(j->step_default);
                    data+=u8R"(;})";

                    data+=u8R"(
constexpr static double max_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"((){return )";
                    data+=QString::number(j->max_value);
                    data+=u8R"(;})";

                    data+=u8R"(
constexpr static double min_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"((){return )";
                    data+=QString::number(j->min_value);
                    data+=u8R"(;})";
                    ///////////////////
                    data+=u8R"(
double )";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=default_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(();)";

                    data+=u8R"(
int step_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=default_step_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(();)";

                    data+=u8R"(
double old_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=default_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(();)";

                    data+=u8R"(
_0x21Q_LineEdit * edit_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=nullptr;)";

                    data+=u8R"(
_0x21Q_LineEdit * edit_step_)";
                    data+=i->unique_name().c_str();
                    data+=u8R"(=nullptr;)";

                }
            }

            data+=u8R"~(
     void setup_ui(){
        using namespace memory ;
        auto && lv=makeStackPointer<_0x21Q_VBoxLayout>();
        super->setLayout(lv.release());
        lv->setSpacing(0);
        lv->setMargin(0);

)~";

            for (const auto &i:values) {

                data+=u8R"({
)";
                if ((i->type()==t_int)||(i->type()==t_double)) {
                    data+=u8R"!(auto && l0=makeStackPointer<_0x21Q_Label>();
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
)!";

                    data+="edit_";
                    data+=i->unique_name().c_str();
                    data+="=e0.pointer();\n";

                    data+="edit_step_";
                    data+=i->unique_name().c_str();
                    data+="=e1.pointer();\n";

                    if (i->type()==t_int) {

                    }
                    else {

                    }

                }


                data+=u8R"(} 
)";
            }/*for*/

            data+=u8R"!~(
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
)!~";

            data+=u8R"(void readState() {
bool ok;
)";
            for (const auto &i:values) {
                data+=u8R"(do{
)";
                if (i->type()==t_int) {
                    data+="auto t=edit_";
                    data+=i->unique_name().c_str();
                    data+="->text();\n";
                    data+=i->unique_name().c_str();
                    data+="= t.toInt(&ok);";
                    data+="\n";
                    data+="if (ok) { break; }\n";
                    data+=i->unique_name().c_str();
                    data+="=default_";
                    data+=i->unique_name().c_str();
                    data+="();\nedit_";
                    data+=i->unique_name().c_str();
                    data+="->setText(\n";
                    data+="QString::number(default_";
                    data+=i->unique_name().c_str();
                    data+="()));\n";
                }
                else if (i->type()==t_double) {
                    data+="auto t=edit_";
                    data+=i->unique_name().c_str();
                    data+="->text();\n";
                    data+=i->unique_name().c_str();
                    data+="= t.toDouble(&ok);";
                    data+="\n";
                    data+="if (ok) { break; }\n";
                    data+=i->unique_name().c_str();
                    data+="=default_";
                    data+=i->unique_name().c_str();
                    data+="();\nedit_";
                    data+=i->unique_name().c_str();
                    data+="->setText(\n";
                    data+="QString::number(default_";
                    data+=i->unique_name().c_str();
                    data+="()));\n";
                }
                data+=u8R"(} while (false);
)";

                data+=u8R"(do{
)";
                if (i->type()==t_int) {
                    data+="auto t=edit_step_";
                    data+=i->unique_name().c_str();
                    data+="->text();\nstep_";
                    data+=i->unique_name().c_str();
                    data+="= t.toInt(&ok);";
                    data+="\n";
                    data+="if (ok) { break; }\nstep_";
                    data+=i->unique_name().c_str();
                    data+="=default_step_";
                    data+=i->unique_name().c_str();
                    data+="();\nedit_step_";
                    data+=i->unique_name().c_str();
                    data+="->setText(\n";
                    data+="QString::number(default_step_";
                    data+=i->unique_name().c_str();
                    data+="()));\n";
                }
                else if (i->type()==t_double) {
                    data+="auto t=edit_step_";
                    data+=i->unique_name().c_str();
                    data+="->text();\nstep_";
                    data+=i->unique_name().c_str();
                    data+="= t.toDouble(&ok);";
                    data+="\n";
                    data+="if (ok) { break; }\nstep_";
                    data+=i->unique_name().c_str();
                    data+="=default_step_";
                    data+=i->unique_name().c_str();
                    data+="();\nedit_step_";
                    data+=i->unique_name().c_str();
                    data+="->setText(\n";
                    data+="QString::number(default_step_";
                    data+=i->unique_name().c_str();
                    data+="()));\n";
                }
                data+=u8R"(} while (false);
)";
            }
            data+=u8R"(}
)";

            data+=u8R"==(

private:
    CPLUSPLUS_OBJECT(_PrivateXDialog)
};

XDialog::XDialog(QWidget *p):_Super(p){
    thisp=new _PrivateXDialog(this);
}

XDialog::~XDialog(){
    delete thisp;
}

)==";

            stream<<data.replace("XDialog",varClassName);
            stream<<endl;
        }

    }

    void writeFile() {
        if (className.empty()) { return; }
        writeHpp();
        writeCpp();
    }

    void doOutPut() {

        {
            lua::checkstack(L,8);
            readLuaFileData();
            if (luaFileData.empty()) { return; }

            StateUpdateDataFromLua state;
            state.super=this;
            lua::pushcfunction(L,&updateDataFromLua);
            lua::pushlightuserdata(L,&state);
            if (lua::OK!=lua::pcall(L,1,0,0)) { return; }
        }

        writeFile();

    }

private:
    CPLUSPLUS_OBJECT(_PrivateMainWindow)
};

MainWindow::MainWindow(QWidget *parent)
    : _Super(parent) {
    thisp=new _PrivateMainWindow;
    using namespace memory;
    auto && varLayout=makeStackPointer<QVBoxLayout>();
    varLayout->setSpacing(0);
    varLayout->setMargin(0);
    this->setLayout(varLayout.release());
    {
        auto && hboxLayout=makeStackPointer<QHBoxLayout>();
        auto && label=makeStackPointer<QLabel>();
        label->setText(QString::fromUtf8(u8R"(选择lua文件:)"));
        hboxLayout->addWidget(label.release());
        auto && textEdit=makeStackPointer<QLineEdit>();
        hboxLayout->addWidget(textEdit.release());
        thisp->luaFilePath=textEdit.pointer();
        auto && button=makeStackPointer<QPushButton>();
        connect(button.pointer(),&QPushButton::clicked,
            this,&MainWindow::_p_get_lua_file);
        hboxLayout->addWidget(button.release());
        button->setText(QString::fromUtf8(u8R"(...)"));
        varLayout->addLayout(hboxLayout.release());
    }
    {
        auto && hboxLayout=makeStackPointer<QHBoxLayout>();
        auto && label=makeStackPointer<QLabel>();
        label->setText(QString::fromUtf8(u8R"(设置输出路径:)"));
        hboxLayout->addWidget(label.release());
        auto && textEdit=makeStackPointer<QLineEdit>();
        hboxLayout->addWidget(textEdit.release());
        thisp->outDir=textEdit.pointer();
        thisp->outDir->setText(
        qApp->applicationDirPath());
        auto && button=makeStackPointer<QPushButton>();
        connect(button.pointer(),&QPushButton::clicked,
            this,&MainWindow::_p_get_out_dir);
        hboxLayout->addWidget(button.release());
        button->setText(QString::fromUtf8(u8R"(...)"));
        varLayout->addLayout(hboxLayout.release());
    }
    {
        auto && spacerItem=makeStackPointer<QSpacerItem>(
            10,10,QSizePolicy::Minimum,QSizePolicy::MinimumExpanding
            );
        varLayout->addSpacerItem(spacerItem.release());
    }
    {
        auto && hboxLayout=makeStackPointer<QHBoxLayout>();
        auto && spacerItem=makeStackPointer<QSpacerItem>(
            10,10,QSizePolicy::MinimumExpanding,QSizePolicy::Minimum
            );
        hboxLayout->addSpacerItem(spacerItem.release());
        auto && pushButton=makeStackPointer<QPushButton>();
        pushButton->setText(QString::fromUtf8(u8R"(执行)"));
        hboxLayout->addWidget(pushButton.release());
        varLayout->addLayout(hboxLayout.release());
        connect(pushButton.pointer(),&QPushButton::clicked,
            this,&MainWindow::_p_do_output);
    }
}

void MainWindow::_p_get_out_dir() {
    auto ans=QFileDialog::getExistingDirectory(this,
        QString::fromUtf8(u8R"(选择输出路径)")
    );
    if (ans.isEmpty()) { return; }
    thisp->outDir->setText(std::move(ans));
}

void MainWindow::_p_get_lua_file() {
    auto ans=QFileDialog::getOpenFileName(this,
        QString::fromUtf8(u8R"(选择lua文件)"),{},
        QString::fromUtf8(u8R"(lua文件(*.lua *.lua.gz *.gz);;所有类型(*.*))"));
    if (ans.isEmpty()) { return; }
    thisp->luaFilePath->setText(std::move(ans));
}

MainWindow::~MainWindow() {
    delete thisp;
}

void MainWindow::_p_do_output() {
    thisp->doOutPut();
}







