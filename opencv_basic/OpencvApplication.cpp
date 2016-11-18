#include "OpencvApplication.hpp"
#include <QtCore/qdir.h>
#include <text/to_plain_text.hpp>
#include <lua/lua.hpp>
#include <list>
#include <vector>
#include <forward_list>
#include <QtWidgets/qproxystyle.h>
#include <atomic>
#include <QtGui/qpainter.h>
#include <QtWidgets/qstylepainter.h>
#include <QtWidgets/qstyleoption.h>

namespace {

inline QString operator""_qs(const char * a,std::size_t n) {
    return QString::fromUtf8(a,static_cast<int>(n));
}

namespace __private {



}/*__private*/
}/**/

class OpencvApplication::_PrivateOpencvApplication {
public:
    QString buildPath;
    QString imageDirPath;
    string_t luaFileData;
    OpencvApplication *thisp;
    lua::State * L=nullptr;

    /*lua state data*/
    std::vector<QString,memory::Allocator<QString>> imageNames;
    std::vector<QPointF,memory::Allocator<QPointF>> point2dData;

    _PrivateOpencvApplication() {
        L=luaL::newstate();
        lua::checkstack(L,1024);
        lua::openlibs(L);
    }

    virtual ~_PrivateOpencvApplication() {
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

    void upateImageSearchDir() {

        {
            QDir dir(thisp->applicationDirPath());
            dir=QDir(dir.absoluteFilePath("Images"_qs));
            if (dir.exists()) {
                QDir::addSearchPath("images"_qs,dir.absolutePath());
            }
        }

        {
            QDir dir(imageDirPath);
            if (dir.exists()) {
                QDir::addSearchPath("images"_qs,dir.absolutePath());
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir(dir.absoluteFilePath("../Images"_qs));
            if (dir.exists()) {
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir(dir.absoluteFilePath("../../Images"_qs));
            if (dir.exists()) {
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir(dir.absoluteFilePath("../../../Images"_qs));
            if (dir.exists()) {
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir(dir.absoluteFilePath("../../../../Images"_qs));
            if (dir.exists()) {
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

        {
            QDir dir(imageDirPath);
            dir=QDir(dir.absoluteFilePath("../../../../../Images"_qs));
            if (dir.exists()) {
                QDir::addSearchPath("images"_qs,dir.absolutePath());
                return;
            }
        }

    }

    class ReadAllImagesState {
    public:
        using list_t=std::list<QString,memory::Allocator<QString>>;
        _PrivateOpencvApplication * pointer;
        list_t imageNames;
    };
    static int lua_readAllImages(lua::State * L) {
        lua::checkstack(L,64);
        auto state=reinterpret_cast<ReadAllImagesState *>(lua::touserdata(L,-1));
        lua::rawgetp(L,LUA_REGISTRYINDEX,state->pointer);
        auto tableIndex=lua::gettop(L);
        if (false==lua::istable(L,-1)) {
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

    ReadAllImagesState::list_t readAllImageNames() {
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
                else if (key==2) {
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
                        case 'x':isXSet=true; ans.setX(lua::tonumberx(L,_value,&isNum)); break;
                        case 'Y':
                        case 'y':isYSet=true; ans.setY(lua::tonumberx(L,_value,&isNum)); break;
                    }
                }
                if (isNum<0) { return false; }
            }
            lua::settop(L,luaNextPos);
        }
        return (isXSet&&isYSet);
    }
    static int lua_readPoint2d(lua::State*L) noexcept(false) {
        lua::checkstack(L,64);
        auto state=
            reinterpret_cast<ReadPoint2dState*>(lua::touserdata(L,-1));

        lua::rawgetp(L,LUA_REGISTRYINDEX,state->pointer);
        auto tableIndex=lua::gettop(L);
        if (false==lua::istable(L,-1)) {
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

        if (lua::istable(L,-1)) {
            lua::rawsetp(L,LUA_REGISTRYINDEX,this);
        }

    }

private:
    CPLUSPLUS_OBJECT(_PrivateOpencvApplication)
};

OpencvApplication::~OpencvApplication() {
    delete _mp;
}

namespace {

class OpenCVAPPStype :public QProxyStyle {
    using _Super=QProxyStyle;
public:
    OpenCVAPPStype(QStyle *a):_Super(a) {
    }
    static std::atomic<int> icon_index;
    static const QIcon getTitleBarIcon() {
        /*通过此函数调整随机数*/
        auto icon_function_=[](int rand_flag_) {
            enum { R_=128,R_0_=R_/4,R_1_=2*R_/4,R_2_=3*R_/4 };
            QImage image_(R_,R_,QImage::Format_RGBA8888);
            image_.fill(QColor(0,0,0,0));
            QPainter painter(&image_);

            QPen pen(QColor(9,0,9,0),0);
            painter.setPen(pen);

            painter.setRenderHints(
                QPainter::HighQualityAntialiasing|
                QPainter::Antialiasing|
                QPainter::TextAntialiasing|
                QPainter::SmoothPixmapTransform
            );

            QPainterPath  p1,p2,p3;

            {
                p1.addEllipse((R_-R_2_)/2,(R_-R_2_)/2,R_2_,R_2_);
                p1.addEllipse((R_-R_1_)/2,(R_-R_1_)/2,R_1_,R_1_);
            }

            {
                p2.addEllipse((R_-R_1_)/2,(R_-R_1_)/2,R_1_,R_1_);
                p2.addEllipse((R_-R_0_)/2,(R_-R_0_)/2,R_0_,R_0_);
            }

            {
                p3.addEllipse((R_-R_0_)/2,(R_-R_0_)/2,R_0_,R_0_);
            }

        switch_flag_:
            switch (rand_flag_) {
                case 0: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p1);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p2);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p3);
                }break;
                case 1: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p2);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p1);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p3);
                case 2: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p2);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p3);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p1);
                }break;
                }break;
                case 3: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p3);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p2);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p1);
                }break;
                case 4: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p3);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p1);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p2);
                }break;
                case 5: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p1);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p3);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p2);
                }break;
                default: {
                    rand_flag_=11-rand_flag_;
                    goto switch_flag_;
                }
            }

            return QIcon(QPixmap::fromImage(std::move(image_)));
        };

        static QIcon ans_[12];
        static bool init_icon_=[icon_function_]() {
            ans_[0]=icon_function_(0);
            ans_[1]=icon_function_(1);
            ans_[2]=icon_function_(2);
            ans_[3]=icon_function_(3);
            ans_[4]=icon_function_(4);
            ans_[5]=icon_function_(5);
            ans_[6]=icon_function_(6);
            ans_[7]=icon_function_(7);
            ans_[8]=icon_function_(8);
            ans_[9]=icon_function_(9);
            ans_[10]=icon_function_(10);
            ans_[11]=icon_function_(11);
            return (rand()==8);
        }();
        ++icon_index;
        if (icon_index>11) { icon_index=0; }
        return ans_[std::min(icon_index.load(),11)];
        (void)(init_icon_);
    }

    void drawComplexControl(
        ComplexControl control,
        const QStyleOptionComplex *option,
        QPainter *painter,
        const QWidget *widget) const override {

        if (control==ComplexControl::CC_TitleBar) {
            const auto * titileBarStyle_=qstyleoption_cast<const QStyleOptionTitleBar *>(option);
            if (titileBarStyle_) {
                auto tbstyle_=const_cast<QStyleOptionTitleBar *>(titileBarStyle_);
                tbstyle_->icon=getTitleBarIcon();
            }
        }

        return _Super::drawComplexControl(control,option,painter,widget);
    }

private:
    CPLUSPLUS_OBJECT(OpenCVAPPStype)
};

std::atomic<int> OpenCVAPPStype::icon_index;

}/*namespace*/

void OpencvApplication::_p_setStype() {
    static QStyle * var=[]() {
        auto ans=new OpenCVAPPStype(qApp()->style());
        qApp()->setStyle(ans);
        return ans;
    }();
}

namespace {
int ErrorCallback(
    int status/*cv::Error::Code*/,
    const char* func_name,
    const char* err_msg,
    const char* file_name,
    int line,
    void* /*userdata*/) {
    return 0;
    (void)status;
    (void)func_name;
    (void)err_msg;
    (void)file_name;
    (void)line;
}
}/*namespace*/

OpencvApplication::OpencvApplication(
        const QString &argBuildPath,
        const QString &argImageDirPath,
        int a,char **b)
    :_Super(a,b) {
    cv::redirectError(&ErrorCallback);
    _mp=new _PrivateOpencvApplication;
    _mp->thisp=this;
    _mp->imageDirPath=argImageDirPath;
    _mp->buildPath=argBuildPath;
    _mp->upateImageSearchDir();
    _mp->updateLuaFile();
    _p_setStype();
}

OpencvApplication * OpencvApplication::instance() {
    return static_cast<OpencvApplication *>(_Super::instance());
}

const OpencvApplication::string_t &
OpencvApplication::getLuaFileData() const {
    return _mp->luaFileData;
}

const QString & OpencvApplication::getBuildPath() const {
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

    return{ _fs,_ls };
}

QPair<const QPointF*,const QPointF*> OpencvApplication::getPoint2d()const {

    if (_mp->point2dData.empty()) {
        auto tmp=_mp->readPoint2d();
        _mp->point2dData.reserve(tmp.size());
        _mp->point2dData.assign(tmp.begin(),tmp.end());
    }

    auto * _fs=&(*_mp->point2dData.begin());
    auto * _ls=_fs+_mp->point2dData.size();

    return{ _fs,_ls };
}

void OpencvApplication::readLuaFile(const QString &arg) {
    return _mp->readLuaFile(arg);
}




