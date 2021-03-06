﻿#ifndef BAIDUUSER_HPP
#define BAIDUUSER_HPP

#include <type_traits>
#include "BaiduImage.hpp"
#include <QtCore/qstring.h>
#include <QtCore/qobject.h>
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>

namespace baidu{

class DoBaiduUserObject : public QNotifyObject {
    Q_OBJECT
public:
    Q_SIGNAL void finished(bool,const QString &,const QImage &);
};

class BaiduPrivateBasic{
public:
    virtual ~BaiduPrivateBasic()=default;
};

class _PrivateBaiduUser;
class BaiduUser : public QObject{
    Q_OBJECT
private:
    using _Super=QObject;
public:
    BaiduUser(std::shared_ptr<QSingleThreadPool>,QObject * /**/=nullptr);
    ~BaiduUser();

public:
    enum BaiduUserState :int {
        StateNone,
        StateLogin,
    };

   BaiduUserState getState()const;
   void setState(BaiduUserState);

   static QByteArray gid();
   static QByteArray currentTime();
   static std::pair<char*,char *> uncompressBaiduImageUrl(char*,const char *const);

   bool isLogin()const;
public:
    Q_SIGNAL void stateChanged(int);
    Q_SIGNAL void loginFinished(bool,const QString &,const QImage &);
    void login(const QString &/*userName*/,const QString &/*passWord*/,const QString&/**/={});
    void downLoad(std::shared_ptr<BaiduImage>);

    _PrivateBaiduUser * getPrivateData()const{
        return reinterpret_cast<_PrivateBaiduUser *>($m$thisp.get());
    }
private:
    std::shared_ptr<BaiduPrivateBasic> $m$thisp;
private:
    CPLUSPLUS_OBJECT(BaiduUser)
};

}/*baidu*/

#endif // BAIDUUSER_HPP


