#include "OpencvApplication.hpp"
#include <QtCore/qdir.h>
#include <text/to_plain_text.hpp>
#include <lua/lua.hpp>
#include <list>
#include <vector>
#include <forward_list>

namespace  {

inline QString operator""_qs(const char * a,std::size_t n){
    return QString::fromUtf8(a,static_cast<int>(n));
}

namespace __private {



}/*__private*/
}/**/

class OpencvApplication::_PrivateOpencvApplication{
public:
    QString buildPath;
    QString imageDirPath;
    string_t luaFileData;
    OpencvApplication *thisp;
    lua::State * L=nullptr;

    /*lua state data*/
    std::vector<QString,memory::Allocator<QString>> imageNames;
    std::vector<QPointF,memory::Allocator<QPointF>> point2dData;

    _PrivateOpencvApplication(){
        L=luaL::newstate();
        lua::checkstack(L,1024);
        lua::openlibs(L);
    }

    virtual ~_PrivateOpencvApplication(){
        lua::close(L);
    }

    void updateLuaFile() {
        const QString varAppName=thisp->applicationName();
        QString luaFileName;

        do {

            {
                QDir dir(thisp->applicationDirPath());
                const auto testName=varAppName+".lua"_qs;
                if (dir.exists(testName)) {
                    luaFileName=dir.absoluteFilePath(testName);
                    break;
                }
            }

            {
                QDir dir(thisp->applicationDirPath());
                const auto testName=varAppName+".lua.gz"_qs;
                if (dir.exists(testName)) {
                    luaFileName=dir.absoluteFilePath(testName);
                    break;
                }
            }

            {
                QDir dir(buildPath);
                const auto testName=varAppName+".lua"_qs;
                if (dir.exists(testName)) {
                    luaFileName=dir.absoluteFilePath(testName);
                    break;
                }
            }

            {
                QDir dir(buildPath);
                const auto testName=varAppName+".lua.gz"_qs;
                if (dir.exists(testName)) {
                    luaFileName=dir.absoluteFilePath(testName);
                    break;
                }
            }

        } while (false);

        luaFileName=luaFileName.trimmed();
        readLuaFile(luaFileName);

    }

    void upateImageSearchDir(){

        {
            QDir dir(thisp->applicationDirPath());
            dir=QDir( dir.absoluteFilePath("Images"_qs) );
            if(dir.exists()){
                QDir::addSearchPath("images"_qs,dir.absolutePath());
            }
        }

        {
            QDir dir(imageDirPath);
            if(dir.exists()){
                QDir::addSearchPath("images"_qs,dir.absolutePath());
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir( dir.absoluteFilePath("../Images"_qs) );
            if(dir.exists()){
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir( dir.absoluteFilePath("../../Images"_qs) );
            if(dir.exists()){
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir( dir.absoluteFilePath("../../../Images"_qs) );
            if(dir.exists()){
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir( dir.absoluteFilePath("../../../../Images"_qs) );
            if(dir.exists()){
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir( dir.absoluteFilePath("../../../../../Images"_qs) );
            if(dir.exists()){
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

    }

    class ReadAllImagesState{
    public:
        using list_t=std::list<QString,memory::Allocator<QString>>;
        _PrivateOpencvApplication * pointer;
        list_t imageNames;
    };
    static int lua_readAllImages(lua::State * L){
        lua::checkstack(L,64);
        auto state=reinterpret_cast<ReadAllImagesState *>(lua::touserdata(L,-1));
        lua::rawgetp(L,LUA_REGISTRYINDEX,state->pointer);
        auto tableIndex=lua::gettop(L);
        if(false==lua::istable(L,-1)){
            lua::pushlstring(L,"can not find table");
            lua::error(L);
        }

        lua::pushlstring(L,"input_images");
        lua::rawget(L,tableIndex);

        auto dataIndex=lua::gettop(L);
        if (false==lua::istable(L,dataIndex)) {
            lua::pushlstring(L,"can not find table:input_images");
            lua::error(L);
        }

        lua::pushnil(L);
        std::size_t strl;
        while (lua::next(L,dataIndex)) {
            const char * strd=luaL::tolstring(L,-1/*value index*/,&strl);
            if ((strl>0)&&strd) {
                state->imageNames.push_back(
                    QString::fromUtf8(strd,strl).trimmed());
            }
            lua::pop(L,2);
        }

        return 0;
    }

    ReadAllImagesState::list_t readAllImageNames(){
        lua::checkstack(L,3);
        ReadAllImagesState state;
        state.pointer=this;
        lua::pushcfunction(L,&lua_readAllImages);
        lua::pushlightuserdata(L,&state);
        lua::pcall(L,1,0,0);
        return std::move(state.imageNames);
    }

    class ReadPoint2dState {
    public:
        _PrivateOpencvApplication * pointer;
        using list_t=std::list<QPointF,memory::Allocator<QPointF>>;
        list_t data;
    };
    static bool readPoint2dItem(lua::State *L,QPointF & ans) {

        const auto tableIndex=lua::gettop(L);
        const auto luaNextPos=tableIndex+1;
        const auto _key=tableIndex+1;
        const auto _value=tableIndex+2;

        lua::pushnil(L);
        int isNum=-1;
        bool isXSet=false;
        bool isYSet=false;
        std::size_t strl=0;
        while (lua::next(L,tableIndex)) {
            if (lua::isinteger(L,_key)) {
                isNum=-1;
                auto key=lua::tointeger(L,_key);
                if (key==1) {
                    isXSet=true;
                    ans.setX(lua::tonumberx(L,_value,&isNum));
                }
                else if(key==2){
                    isYSet=true;
                    ans.setY(lua::tonumberx(L,_value,&isNum));
                }
                if (isNum<0) { return false; }
            }
            else {
                isNum=-1;
                auto key=luaL::tolstring(L,_key,&strl);
                if (key&&(strl>0)) {
                    switch (*key) {
                        case 'X':
                        case 'x':isXSet=true;ans.setX(lua::tonumberx(L,_value,&isNum));break;
                        case 'Y':
                        case 'y':isYSet=true;ans.setY(lua::tonumberx(L,_value,&isNum)); break;
                    }
                }
                if (isNum<0) { return false; }
            }
            lua::settop(L,luaNextPos);
        }
        return (isXSet&&isYSet);
    }
    static int lua_readPoint2d(lua::State*L) noexcept(false){
        lua::checkstack(L,64);
        auto state=
            reinterpret_cast<ReadPoint2dState*>(lua::touserdata(L,-1));

        lua::rawgetp(L,LUA_REGISTRYINDEX,state->pointer);
        auto tableIndex=lua::gettop(L);
        if(false==lua::istable(L,-1)){
            lua::pushlstring(L,"can not find table");
            lua::error(L);
        }

        lua::pushlstring(L,"input_data_2d");
        lua::rawget(L,tableIndex);

        auto dataIndex=lua::gettop(L);
        if (false==lua::istable(L,dataIndex)) {
            lua::pushlstring(L,"can not find table:input_images");
            lua::error(L);
        }

        lua::pushnil(L);
        //constexpr static const auto _key=-2;
        constexpr static const auto _value=-1;
        const auto luaNextPos=dataIndex+1;
        QPointF ansi;
        while (lua::next(L,dataIndex)) {
            if (lua::istable(L,_value)) {
                if (readPoint2dItem(L,ansi)) {
                    state->data.push_back(ansi);
                }
                else {
                    state->data.clear();
                    lua::pushlstring(L,"read point 2d error");
                    lua::error(L);
                }
            }
            lua::settop(L,luaNextPos);
        }

        return 0;
    }
    ReadPoint2dState::list_t readPoint2d() {
        lua::checkstack(L,3);
        ReadPoint2dState state;
        state.pointer=this;
        lua::pushcfunction(L,&lua_readPoint2d);
        lua::pushlightuserdata(L,&state);
        lua::pcall(L,1,0,0);
        return std::move(state.data);
    }

    void readLuaFile(const QString &luaFileName) {
        /*check state size*/
        lua::checkstack(L,8);
        /*reset lua state*/
        lua::pushnil(L);
        lua::rawsetp(L,LUA_REGISTRYINDEX,this);
        /*clear c++ state data*/
        point2dData.clear();
        imageNames.clear();
        luaFileData.clear();

        if (luaFileName.isEmpty()) {
            return;
        }

        QFile file(luaFileName);
        if (file.open(QIODevice::ReadOnly)) {
            const QByteArray varData=file.readAll();
            file.close();
            if (varData.isEmpty()) { return; }
            auto varPlainText=
                text::to_plain_text(varData.begin(),varData.end());
            luaFileData=string_t(varPlainText.begin(),
                varPlainText.end());
        }
        else {
            return;
        }

        /*put the app to top*/
        luaL::loadstring(L,luaFileData.c_str());
        lua::pcall(L,0,lua::MULTRET,0);

        if(lua::istable(L,-1)){
            lua::rawsetp(L,LUA_REGISTRYINDEX,this);
        }

    }

private:
    CPLUSPLUS_OBJECT(_PrivateOpencvApplication)
};

OpencvApplication::~OpencvApplication(){
    delete _mp;
}

OpencvApplication::OpencvApplication(
        const QString &argBuildPath,
        const QString &argImageDirPath,
        int a, char **b)
    :_Super(a,b){
    _mp=new _PrivateOpencvApplication;
    _mp->thisp=this;
    _mp->imageDirPath=argImageDirPath;
    _mp->buildPath=argBuildPath;
    _mp->upateImageSearchDir();
    _mp->updateLuaFile();
}

OpencvApplication * OpencvApplication::instance(){
    return static_cast<OpencvApplication *>(_Super::instance());
}

const OpencvApplication::string_t &
OpencvApplication::getLuaFileData() const {
    return _mp->luaFileData;
}

const QString & OpencvApplication::getBuildPath() const{
    return _mp->buildPath;
}

QPair<const QString*,const QString*> OpencvApplication::getAllImageNames()const {

    if (_mp->imageNames.empty()) {
        auto tmp=_mp->readAllImageNames();
        _mp->imageNames.reserve(tmp.size());
        for (auto & i:tmp) {
            _mp->imageNames.push_back(std::move(i));
        }
    }

    QString * _fs=&(*_mp->imageNames.begin());
    QString * _ls=_fs+_mp->imageNames.size();

    return{_fs,_ls};
}

QPair<const QPointF*,const QPointF*> OpencvApplication::getPoint2d()const {

    if (_mp->point2dData.empty()) {
        auto tmp=_mp->readPoint2d();
        _mp->point2dData.reserve(tmp.size());
        _mp->point2dData.assign(tmp.begin(),tmp.end());
    }

    auto * _fs=&(*_mp->point2dData.begin());
    auto * _ls=_fs+_mp->point2dData.size();

    return{_fs,_ls};
}

void OpencvApplication::readLuaFile(const QString &arg) {
    return _mp->readLuaFile(arg);
}




