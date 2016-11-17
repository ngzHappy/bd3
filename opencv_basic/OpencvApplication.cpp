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
    std::vector<QString,memory::Allocator<QString>> imageNames;

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

        /*put the app to top*/
        luaL::loadstring(L,luaFileData.c_str());
        lua::pcall(L,0,lua::MULTRET,0);

        if(lua::istable(L,-1)){
            lua::rawsetp(L,LUA_REGISTRYINDEX,this);
        }

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








