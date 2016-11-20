#include <list>
#include <regex>
#include <QtCore>
#include <vector>
#include <cstring>
#include <QtWidgets>
#include <lua/lua.hpp>
#include "MainWindow.hpp"
#include <text/to_plain_text.hpp>

namespace {

template<typename T>
using vector=std::vector<T,memory::Allocator<T>>;
using string=std::basic_string<char,
    std::char_traits<char>,memory::Allocator<char> >;
template<typename T>
using list=std::list<T,memory::Allocator<T>>;

}/*namespace*/

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
        t_int,
        t_double,
        t_enum
    };

    class Value {
    public:
        virtual ~Value() {}
        virtual const string & unique_name()const=0;
        virtual const string & readable_name()const=0;
        virtual Type type() const { return t_unknow; }
    };

    vector<std::unique_ptr<const Value>> values;
    class EnumValue final :public Value {
    public:
        class KeyVale {
        public:
            string key;
            string value;
            KeyVale()=default;
            KeyVale(string &&k,string &&v):key(std::move(k)),value(std::move(v)) {}
        private:
            CPLUSPLUS_OBJECT(KeyVale)
        };
        string name;
        string u_name;
        list<KeyVale> enums;

        void setName(string _name) {
            name=std::move(_name);
            const static std::regex rg("X");
            u_name=std::regex_replace(name,rg,"_x_");
            u_name+="_0x2e";
        }
        const string & readable_name()const override { return name; }
        Type type() const override { return t_enum; }
        const string & unique_name()const override { return u_name; }
    private:
        CPLUSPLUS_OBJECT(EnumValue)
    };

    class IntValue final :public Value {
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
        const string & readable_name()const override { return name; }
        Type type() const override { return t_int; }
        const string & unique_name()const override { return u_name; }
    private:
        CPLUSPLUS_OBJECT(IntValue)
    };

    class DoubleValue final :public Value {
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
        const string & readable_name()const override { return name; }
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

    static void readEnumValues(lua::State *L,
        EnumValue * value) {

        auto tablePos=lua::gettop(L);
        auto keypos=tablePos+1;
        auto valuePos=tablePos+2;
        lua::pushnil(L);
        const char * str;
        size_t strl;
        string enumName;
        string enumValue;
        while (lua::next(L,tablePos)) {
            if (lua::istable(L,valuePos)) {
                const auto & kvTablePos=valuePos;
                lua::rawgeti(L,kvTablePos,1);
                str=luaL::tolstring(L,-1,&strl)/*enum name*/;
                enumName.assign(str,strl);
                lua::rawgeti(L,kvTablePos,2);
                str=luaL::tolstring(L,-1,&strl)/*enum value*/;
                enumValue.assign(str,strl);
                value->enums.emplace_back(std::move(enumName)
                    ,std::move(enumValue));
            }
            lua::settop(L,keypos);
        }

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
                        else if (str_cmp(skey,strl,"enum_value")) {
                            auto && value=memory::makeStackPointer<EnumValue>();
                            lua::rawgeti(L,valuePos,2);
                            skey=lua::tolstring(L,-1,&strl);
                            key.assign(skey,strl);
                            value->setName(std::move(key));
                            if (lua::rawgeti(L,valuePos,3)==lua::TTABLE) {
                                readEnumValues(L,value);
                                if (false==value->enums.empty()) {
                                    values.push_back(value.toConstStdPointer());
                                }
                            }
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
                            varSignal+=j->readable_name().c_str();
                            varSignal+=" */";
                        }break;
                        case t_double: {
                            auto j=static_cast<const DoubleValue*>(i.get());
                            varSignal+="double /* ";
                            varSignal+=j->readable_name().c_str();
                            varSignal+=" */";
                        }break;
                        case t_enum: {
                            auto j=static_cast<const EnumValue*>(i.get());
                            varSignal+="int /*enum: ";
                            varSignal+=j->readable_name().c_str();
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
            data.reserve(1024*32);
            data+=u8R"~(#include "XDialog.hpp"
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
setup_ui()/*建立gui并连接信号槽*/;
readState()/*更新gui数据*/;
}

)~";
            /**write values*******************************/
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
double step_)";
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
                else if (i->type()==t_enum) {
                    auto j=static_cast<const EnumValue *>(i.get());

                    data+=u8R"(
_0x21Q_ComboBox * enum_)";
                    data+=j->unique_name().c_str();
                    data+="=nullptr;";

                    data+=u8R"(
int/*enum*/old_)";
                    data+=j->unique_name().c_str();
                    data+="=static_cast<int/*enum*/>( ";
                    data+=j->enums.front().value.c_str();
                    data+=" );";

                    data+=u8R"(
int/*enum*/)";
                    data+=j->unique_name().c_str();
                    data+="=static_cast<int/*enum*/>( ";
                    data+=j->enums.front().value.c_str();
                    data+=" );";

                    /* int map__x_Dialogtest2_0x2e(int arg) {

                    }*/
                    data+=u8R"(
int/*enum*/map_)";
                    data+=j->unique_name().c_str();
                    data+="(int arg) {\n";
                    data+="switch(arg){\n";
                    {
                        int ii=0;
                        for (const auto & i:j->enums) {
                            data+="\ncase "+QString::number(ii)+" : return ";
                            data+="static_cast<int/*enum*/>( ";
                            data+=i.value.c_str();
                            data+=" );";
                            data+="/* ";
                            data+=i.key.c_str();
                            data+=" */";
                            ++ii;
                        }
                    }
                    data+="\n}\n";

                    data+="return ";
                    data+="static_cast<int/*enum*/>( ";
                    data+=j->enums.front().value.c_str();
                    data+=QString::fromUtf8(u8" );/*默认值*/");

                    data+="\n}\n";
                }
            }

            /**void setup_ui*******************************/
            data+=u8R"~(
     void setup_ui(){
        using namespace memory ;
/*窗口布局*/
        auto && lv=makeStackPointer<_0x21Q_VBoxLayout>();
        super->setLayout(lv.release());
        lv->setSpacing(0);
        lv->setMargin(0);

)~";

            for (const auto &i:values) {

                data+=u8R"({
)";
                if (i->type()==t_enum) {
                    data+=u8R"~=:;:=~(
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

)~=:;:=~";

                    data+="l0->setText(u8R\"__(";
                    data+=i->readable_name().c_str();
                    data+=")__\" \" : \" );";
                    data+=QString::fromUtf8(u8R"(/*设置label name*/
)");

                    auto j=static_cast<const EnumValue*>(i.get());
                    for (const auto & e:j->enums) {
                        data+=u8R"_(
 c0->addItem( u8R"|||()_";
                        data+=e.key.c_str();
                        data+=u8R"_()|||" );)_";
                    }

                    data+=QString::fromUtf8(u8R"~=:;:=~(
/*连接信号槽*/
            c0->connect(c0.pointer(),
                T_0x21Q_CurrentIndexChanged(&QComboBox::currentIndexChanged),
                super,
                [this](int) {checkDo(); });
)~=:;:=~");

                    data+="enum_";
                    data+=i->unique_name().c_str();
                    data+="=c0;\n";

                    data+="\n";
                }
                else if ((i->type()==t_int)||(i->type()==t_double)) {
                    data+=u8R"!(
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
)!";

                    data+="l0->setText(u8R\"__(";
                    data+=i->readable_name().c_str();
                    data+=")__\" \" : \" );";
                    data+=QString::fromUtf8(u8R"(/*设置label name*/
)");

                    data+="edit_";
                    data+=i->unique_name().c_str();
                    data+="=e0.pointer();\n";

                    data+="edit_step_";
                    data+=i->unique_name().c_str();
                    data+="=e1.pointer();\n";

                    if (i->type()==t_int) {
                        data+=u8R"~=:;:=~(
/*int value 检查器*/
auto && v0=makeStackPointer<_0x21Q_IntValidator>();
auto && v1=makeStackPointer<_0x21Q_IntValidator>();
)~=:;:=~";
                    }
                    else {
                        data+=u8R"~=:;:=~(
/*double value 检查器*/
auto && v0=makeStackPointer<_0x21Q_DoubleValidator>();
auto && v1=makeStackPointer<Step_0x21Q_DoubleValidator>();
)~=:;:=~";
                    }

                    data+="v0->setRange(min_";
                    data+=i->unique_name().c_str();
                    data+="(),max_";
                    data+=i->unique_name().c_str();
                    data+="());\n";

                    if (i->type()==t_int) {
                        data+="v1->setRange(-9999,9999);\n";
                    }

                    data+=u8R"~=:;:=~(v0.release()->setParent(e0);
            v1.release()->setParent(e1);
            e0->setValidator(v0);
            e1->setValidator(v1);
)~=:;:=~";
                    data+="edit_";
                    data+=i->unique_name().c_str();
                    data+="=e0.pointer();\n";

                    data+="edit_step_";
                    data+=i->unique_name().c_str();
                    data+="=e1.pointer();\n";

                    QString aWrite=u8R"~=:;:=~(
/*连接信号槽*/
/*连接信号槽*/p0->connect(p0.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {add_XXXXXXXXXX(); });
/*连接信号槽*/p1->connect(p1.pointer(),&QToolButton::clicked,
/*连接信号槽*/super,[this](bool) {sub_XXXXXXXXXX(); });
)~=:;:=~";
                    data+=aWrite.replace("XXXXXXXXXX",
                        i->unique_name().c_str());

                }/*int or double*/


                data+=u8R"(} 
)";
            }/*for*/

            data+=u8R"!~(
{/*创建中间空白*/
            auto && ls=makeStackPointer<_0x21Q_SpacerItem>(
                1,1,QSizePolicy::Minimum,
                QSizePolicy::MinimumExpanding
                );
            lv->addSpacerItem(ls.release());
        })!~";

            data+=
                u8R"!~(
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
         )!~";

            data+=u8R"~=:;:=~(
 super->connect(
                        pb.pointer(),
                        &QPushButton::clicked,
                        super,
                        [this](bool){checkDo();}
                        );
)~=:;:=~";

            data+=u8R"!~(
} 
)!~";

            data+=u8R"!~(
}/*function end*/
)!~";

            /**readState*******************************/
            data+=u8R"(void readState() {
bool ok;
)";
            for (const auto &i:values) {
                if (i->type()==t_enum) {
                    QString aWrite=u8R"___(
{XXX=map_XXX(
enum_XXX->currentIndex());}
)___";
                    data+=aWrite.replace("XXX",
                        i->unique_name().c_str());
                }
                else {
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
                }/*type int or double*/
            }
            data+=u8R"(}
)";
            /**void directDo*******************************/
            data+="void directDo() {";
            data+="\n";
            data+="super->valueChanged(";
            {
                bool isFirst=true;
                for (const auto & i:values) {
                    if (isFirst) { isFirst=false; }
                    else {
                        data+=u8R"(
,)";
                    }
                    data+=i->unique_name().c_str();
                }
                data+=");\n";
            }
            data+="}";
            data+="\n";
            /**void directDo*******************************/
            data+=" bool isStateChange() {\n";
            data+=" auto ans=false;\n";
            for (const auto & i:values) {
                data+="if (old_";
                data+=i->unique_name().c_str();
                data+="!=";
                data+=i->unique_name().c_str();
                data+="){\n";
                data+="ans=true;\n";
                data+="old_";
                data+=i->unique_name().c_str();
                data+="=";
                data+=i->unique_name().c_str();
                data+=";\n}\n";
            }
            data+="return ans;\n}\n";

            /**void checkDo*******************************/
            data+=u8R"~(

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

)~";

            /*add sub 函数*/
            for (const auto & i:values) {
                if ((i->type()==t_int)||(i->type()==t_double)) {
                    QString aWrite=QString::fromUtf8(u8R"_:_(
 void add_XXXXXXXXXX() {
        readState()/*获得当前状态*/;
        XXXXXXXXXX+=step_XXXXXXXXXX/*增加值*/;
        check_max(XXXXXXXXXX,max_XXXXXXXXXX())/*检测最大值*/;
        check_min(XXXXXXXXXX,min_XXXXXXXXXX())/*检测最小值*/;
        edit_XXXXXXXXXX->setText(
            QString::number(XXXXXXXXXX))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }
)_:_");
                    data+=aWrite.replace("XXXXXXXXXX",i->unique_name().c_str());

                    aWrite=QString::fromUtf8(u8R"_:_(
 void sub_XXXXXXXXXX() {
        readState()/*获得当前状态*/;
        XXXXXXXXXX-=step_XXXXXXXXXX/*增加值*/;
        check_max(XXXXXXXXXX,max_XXXXXXXXXX())/*检测最大值*/;
        check_min(XXXXXXXXXX,min_XXXXXXXXXX())/*检测最小值*/;
        edit_XXXXXXXXXX->setText(
            QString::number(XXXXXXXXXX))/*重设gui值*/;
        if (isStateChange()) { directDo(); }/*发送值变化信号*/
    }
)_:_");

                    data+=aWrite.replace("XXXXXXXXXX",i->unique_name().c_str());
                }
            }

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







