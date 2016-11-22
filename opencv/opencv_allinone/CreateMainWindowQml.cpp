#include <list>
#include <QtCore>
#include "CreateMainWindowQml.hpp"
#include <QtWidgets/qapplication.h>
#include <OpenCVUtility.hpp>
#include "MainWindow.hpp"

#include <lua/lua.hpp>
#include <quazip/quazip.h>
#include <quazip/quazipfile.h>
#include <quazip/quazipdir.h>
#include <cplusplus_basic.hpp>

namespace {
inline QString operator""_qs(const char * arg,size_t argl) {
    return QString::fromUtf8(arg,argl);
}

namespace LuaUtility {

template<typename _QIODevice_>
void _p_loadFile_read(
    _QIODevice_ & zFile,
    luaL_Buffer & _v_buffer
) {
    enum { SIZE_=1024*4 };
    std::unique_ptr<char,void(*)(char *)> __data
    (new char[SIZE_+8],[](char * _d) {delete[] _d; });
    __data.get()[0]=0; 
    __data.get()[1]=0; 
    __data.get()[2]=0;
    __data.get()[SIZE_]=0;
    __data.get()[SIZE_+1]=0;
    __data.get()[SIZE_+2]=0;
    __data.get()[SIZE_+3]=0;
    auto size__=zFile.read(__data.get(),SIZE_);

    /*加载第一段数据*/
    /*-bom :0xEF0xBB0xBF*/
    if (
        (__data.get()[0])==char(0x00ef)&&
        (__data.get()[1])==char(0x00bb)&&
        (__data.get()[2])==char(0x00bf)&&
        size__>3
        ) {
        luaL_addlstring(&_v_buffer,__data.get()+3,size__-3);
    }
    else {
        luaL_addlstring(&_v_buffer,__data.get(),size__ );
    }

    while ((size__=zFile.read(__data.get(),SIZE_))>0) {
        luaL_addlstring(&_v_buffer,__data.get(),size__);
    }
}

template<typename _T_,typename _U_>
inline int _p_loadFile(
    lua_State * L,
    _T_ && _a_fileName_,
    _U_ && _a_zip_file_name_
) {

    const auto top_lock_=lua_gettop(L);
    bool _is_Ok_=true;

    /*load string*/
    try {

        const QString _a_fileName=_a_fileName_.trimmed();
        const QString _a_zip_file_name=_a_zip_file_name_.trimmed();

        if (_a_fileName.isEmpty()) { return 0; }

        auto _v__buffer
            =std::shared_ptr<luaL_Buffer>(
                new luaL_Buffer,
                [L](luaL_Buffer * _buffer_) {
            luaL_pushresult(_buffer_);
            delete _buffer_;
        }
        );

        auto & _v_buffer=*_v__buffer;

        luaL_buffinit(L,&_v_buffer);

        if (_a_fileName.endsWith(".zip",Qt::CaseInsensitive)) {
            QuaZip zip_file_(_a_fileName);
            if (zip_file_.open(QuaZip::mdUnzip)) {
                if (zip_file_.setCurrentFile(_a_zip_file_name)) {
                    QuaZipFile zFile(&zip_file_);
                    if (zFile.open(QIODevice::ReadOnly)) {
                        _p_loadFile_read(zFile,_v_buffer);
                    }
                    else {
                        qDebug().noquote()<<"can not open zipfile"<<_a_zip_file_name;
                        throw nullptr;
                    }
                }
                else {
                    qDebug().noquote()<<"can not find zipfile"<<_a_zip_file_name;
                    throw nullptr;
                }
            }
            else {
                qDebug().noquote()<<"can not open file"<<_a_fileName;
                throw nullptr;
            }

        }
        else {
            QFile file_(_a_fileName);
            if (file_.open(QIODevice::ReadOnly)) {
                _p_loadFile_read(file_,_v_buffer);
            }
            else {
                qDebug().noquote()<<"can not open file"<<_a_fileName;
                throw nullptr;
            }
        }

    }
    catch (...) {
        _is_Ok_=false;
    }

    if (_is_Ok_) {
        size_t __size__;
        const char * __string__=lua_tolstring(L,-1,&__size__);
        if( luaL_loadbuffer(L,__string__,__size__,__string__) == LUA_OK ){
            assert( (lua_gettop(L)-top_lock_)==2 );
            lua_copy(L,-1,-2);
            lua_settop(L,top_lock_+1);
            return 1;
        }
        else {
            const char * _error_=luaL_tolstring(L,-1,&__size__);
            if ( __size__ && _error_ ) {
                qDebug()<<"error on build "<<QByteArray(_error_,__size__);
            }
            lua_settop(L,top_lock_);
            return 0;
        }
    }
    else {
        lua_settop(L,top_lock_);
        return 0;
    }

    return 1;
}

inline bool loadFile(
    lua::State* L,
    const QString & fileName,
    const QString & zipFileName) {
    return _p_loadFile(L,fileName,zipFileName);
}

}/*LuaUtility*/

}/*namespace*/

CreateMainWindowQml::CreateMainWindowQml() {

}

std::shared_ptr<CreateMainWindowQml> CreateMainWindowQml::instance() {
    std::shared_ptr<CreateMainWindowQml> varAns{
        new CreateMainWindowQml,
        [](auto * varD) {delete varD; }
    };
    return std::move(varAns);
}

void  CreateMainWindowQml::createAllInOneItemQml() {
    {
        QString varFileName=QDir::cleanPath(qApp->applicationDirPath()+"/AllInOneItem.qml");
        do {
            {
                QFileInfo info(varFileName);
                if (info.exists()) { break; }
            }
            QFile varFile(varFileName);
            varFile.open(QIODevice::WriteOnly);
            QResource varSource(":/MainWindowAllInOne/qml/AllInOneItem.qml");
            if (varSource.isCompressed()) {
                varFile.write(qUncompress(varSource.data(),varSource.size()));
            }
            else {
                varFile.write(
                    (char *)(varSource.data()),
                            varSource.size()
                );
            }
            varFile.flush();
        } while (false);

        {
            QString varFileName=QDir::cleanPath(qApp->applicationDirPath()+"/YScroallBar.qml");
            {
                QFileInfo info(varFileName);
                if (info.exists()) { return; }
            }
            QFile varFile(varFileName);
            varFile.open(QIODevice::WriteOnly);
            QResource varSource(":/MainWindowAllInOne/qml/YScroallBar.qml");
            if (varSource.isCompressed()) {
                varFile.write(qUncompress(varSource.data(),varSource.size()));
            }
            else {
                varFile.write(
                    (char *)(varSource.data()),
                            varSource.size()
                );
            }
            varFile.flush();
        }
    }
}

namespace __private {
static std::map<QString,QString> gen_old_configure();
static std::map<QString,QString> gen_configure();
static void save_AllInOneMainWindowQml(const std::list<std::pair<QString,QString>>&);
static void write_AllInOneMainWindowQml(QFile &,const std::map<QString,QString>&);
}

void  CreateMainWindowQml::createAllInOneMainWindowQml() {
    QString varFileName=QDir::cleanPath(qApp->applicationDirPath()+"/AllInOneMainWindow.qml");
    QFile varFile(varFileName);
    varFile.open(QIODevice::WriteOnly|QIODevice::Text);

    auto configure=__private::gen_configure();
    {/*设置保存的arg*/
        const auto oldConfigure=__private::gen_old_configure();
        const auto eit=oldConfigure.end();
        for (auto & i:configure) {
            auto pos=oldConfigure.find(i.first);
            if (eit==pos) { continue; }
            i.second=pos->second;
        }
    }
    __private::write_AllInOneMainWindowQml(varFile,configure);
    varFile.flush();
}

CreateMainWindowQml::~CreateMainWindowQml() {

}

void MainWindow::_save() {
    int __i=0;
    QString key,value;
    std::list<std::pair<QString,QString>> ans;
    for (;;) {
        auto ___i=__i++;
        key=getProjectName(___i);
        value=getStartString(___i);
        if (key==value) {
            if (key=="@nil") { break; }
        }
        ans.emplace_back(std::move(key),std::move(value));
    }
    __private::save_AllInOneMainWindowQml(ans);
}

namespace __private {
static void save_AllInOneMainWindowQml(
    const std::list<std::pair<QString,QString>>& data
) {

    if (data.empty()) {
        QuaZip zip(qApp->applicationDirPath()+"/all_in_one.zip");
        if (zip.open(QuaZip::mdCreate)) {
            QuaZipFile file(&zip);
            if (file.open(QIODevice::WriteOnly,QuaZipNewInfo("all_in_one.lua"))) {
                file.write("--[[nullfile--]]\n");
            }
        }
        return;
    }

    auto __L=std::shared_ptr<lua::State>(
                luaL::newstate(),
                [](auto L) {lua::close(L); });
    lua::openlibs(__L.get());

    auto L=__L.get();
    lua_createtable(L,data.size(),0);
    lua_pushvalue(L,-1);
    lua_setglobal(L,"app");
    const auto app_table=lua_gettop(L);

    int app_table_index=0;
    for (const auto & i:data) {
        lua_createtable(L,2,0);
        const auto table_index=lua_gettop(L);
        lua_pushvalue(L,-1);
        lua_rawseti(L,app_table,++app_table_index);

        {
            const QByteArray data__=i.first.toLocal8Bit();
            lua_pushlstring(L,data__.constData(),data__.size());
            lua_rawseti(L,table_index,1);
        }

        {
            const QByteArray data__=i.second.toLocal8Bit();
            lua_pushlstring(L,data__.constData(),data__.size());
            lua_rawseti(L,table_index,2);
        }

        lua_settop(L,table_index-1);
    }

    lua_pushcfunction(L,&luaL::function_table_tostring);
    //lua_pushstring(L,"app");
    lua_pushvalue(L,app_table);
    lua_pcall(L,1,LUA_MULTRET,0);

    size_t len;
    auto * about_to_write=lua_tolstring(L,-1,&len);

    {
        QFileInfo info(qApp->applicationDirPath()+"/all_in_one.lua");
        if (info.exists()) {
            QFile file(qApp->applicationDirPath()+"/all_in_one.lua");
            if (file.open(QIODevice::WriteOnly)) {
                QTextStream stream(&file);
                stream.setCodec("UTF-8");
                stream<<bom;
                stream<<QLatin1Literal(about_to_write,
                    static_cast<int>(len));
            }
            return;
        }
    }

    if (about_to_write) {
        QuaZip zip(qApp->applicationDirPath()+"/all_in_one.zip");
        if (zip.open(QuaZip::mdCreate)) {
            QuaZipFile file(&zip);
            if (file.open(QIODevice::WriteOnly,QuaZipNewInfo("all_in_one.lua"))) {
                file.write(about_to_write,len);
            }
        }
    }
    else {
        QuaZip zip(qApp->applicationDirPath()+"/all_in_one.zip");
        if (zip.open(QuaZip::mdCreate)) {
            QuaZipFile file(&zip);
            if (file.open(QIODevice::WriteOnly,QuaZipNewInfo("all_in_one.lua"))) {
                file.write("--[[nullfile--]]\n");
            }
        }
    }
}
}

namespace __private {
static void write_AllInOneMainWindowQml(
    QFile & file,
    const std::map<QString,QString>& configure) {
    QTextStream stream_(&file);
    stream_.setCodec(QTextCodec::codecForName("UTF-8"));

    stream_<<u8R"_!!_(/*qml main window*/
/*
此文件由程序生成
任何对于此文件的修改都是无效的
*/
import QtQuick 2.5
import QtQml.Models 2.2

/*rootWindow*/

Rectangle {
    width: 1000;
    height: 1000;
    color: Qt.rgba(0.5,0.6,0.5,1);
    id : rootItem;

    function getProjectName(n){
        if(n>=itemModel.count){return "@nil";}
        return itemModel.get(n).projectName;
    }
    function getStartString(n){
        if(n>=itemModel.count){return "@nil";}
        return itemModel.get(n).startString;
    }

    ObjectModel {
        id: itemModel;
        /****************************************/
)_!!_"_qs;

    for (const auto & i:configure) {
        /*AllInOneItem{projectName:"0";startString:"";width: rootItem.width;}*/
        stream_<<"AllInOneItem{projectName:";
        stream_<<u8R"(")"<<i.first<<u8R"(";)";
        stream_<<"startString:";
        stream_<<u8R"(")"<<i.second<<u8R"(";width: rootItem.width;})";
        stream_<<endl;
    }

    stream_<<u8R"_11_(
    /****************************************/
    }
    ListView {
        anchors.fill: parent;
        model: itemModel;
        YScroallBar{view:parent;}
    }

}


)_11_"_qs;

}
}

namespace __private {
static std::map<QString,QString> gen_configure() {
    std::map<QString,QString> ans_;

    QDir dir(qApp->applicationDirPath());

    const QString app_name_{ qApp->applicationName() };
    const QString arg_;
    dir.setFilter(QDir::Executable|QDir::Files);
    auto info=dir.entryInfoList();
    for (const auto & i:info) {
        /*name??? 因为有后缀,这里不跨平台 */
        QString name_=i.completeBaseName();
        if (name_==app_name_) { continue; }
#if defined(Q_OS_WIN32)
#else
        if (name_.startsWith("libcore_utilityd.so")) { continue; }
        if (name_.startsWith("libcore_utility.so")) { continue; }
#endif
        /*on windows it's ???.exe ???.bat ...but on linux it will be ??? */
        name_=i.fileName();
        ans_.insert({ std::move(name_),arg_ });
    }

    return std::move(ans_);
}
}

namespace __private {
/*
app={
{"xxx","-l xvsdf"},
{"yyy","-l xvsdf"},
}
*/

static std::map<QString,QString> gen_old_configure() {
    /*all_in_one.lua;*/
    /*all_in_one.zip;*/
    QString dirPath_=QDir::cleanPath(qApp->applicationDirPath());
    auto _LuaState_=std::shared_ptr<lua::State>(
        luaL::newstate(),
        [](auto L) {lua::close(L); });
    lua::openlibs(_LuaState_.get());

    auto * L=_LuaState_.get();

    bool isExist=false;

    {
        QFileInfo info(dirPath_+"/all_in_one.zip");
        if (info.exists()) {
            isExist=
                LuaUtility::loadFile(L,
                    dirPath_+"/all_in_one.zip",
                    "all_in_one.lua");
        }
    }

    if (isExist==false) {
        QFileInfo info(dirPath_+"/all_in_one.lua");
        if (info.exists()) {
            isExist=
                LuaUtility::loadFile(L,
                    dirPath_+"/all_in_one.lua",
                    "all_in_one.lua");
        }
    }

    if (isExist==false) { return{}; }

    if (0==lua_pcall(L,0,LUA_MULTRET,-1)) {
        std::map<QString,QString> ans;
        //luaL_dostring(L,"return app");
        if (lua_istable(L,-1)==false) { return{}; }

        const auto table_=lua_gettop(L);
        lua_pushnil(L);
        while (lua_next(L,table_)) {
            if (lua_istable(L,-1)) {
                auto table_kv=lua_gettop(L);
                QString key,value;
                lua_rawgeti(L,table_kv,1);
                {
                    size_t len;
                    auto *str=luaL_tolstring(L,-1,&len);
                    if (str==nullptr) { lua_settop(L,table_kv-1); continue; }
                    key=QString::fromUtf8(str,len);
                }
                lua_rawgeti(L,table_kv,2);
                {
                    size_t len;
                    auto *str=luaL_tolstring(L,-1,&len);
                    if (str==nullptr) { lua_settop(L,table_kv-1); continue; }
                    value=QString::fromUtf8(str,len);
                }
                lua_settop(L,table_kv-1);
                ans.insert({ std::move(key),std::move(value) });
            }
            else {
                lua_pop(L,1);
            }
        }

        return std::move(ans);
    }

    return{};
}

}

