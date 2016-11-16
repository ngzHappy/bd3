#include "OpencvApplication.hpp"
#include <QtCore/qdir.h>

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

}

OpencvApplication * OpencvApplication::instance(){
    return static_cast<OpencvApplication *>(_Super::instance());
}

const OpencvApplication::string_t & 
OpencvApplication::getLuaFileData() const {
    return _mp->luaFileData;
}











