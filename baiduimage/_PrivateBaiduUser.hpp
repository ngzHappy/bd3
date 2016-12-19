#ifndef _PRIVATEBAIDUUSER_HPP
#define _PRIVATEBAIDUUSER_HPP

#include <regex>
#include <atomic>
#include "BaiduUser.hpp"
#include <QtQml/qjsvalue.h>
#include <QtQml/qjsengine.h>
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>
#include <QtNetwork/qnetworkcookie.h>
#include <QtNetwork/qnetworkcookiejar.h>
#include <QtNetwork/qnetworkaccessmanager.h>

namespace baidu {

class BaiduUser;

class NetworkCookieJar :public QNetworkCookieJar {
    Q_OBJECT
private:
    using _Super_=QNetworkCookieJar;
    class light_mutex : std::recursive_mutex {
        using _super_t_=std::recursive_mutex;
    public:
        using _super_t_::try_lock;
        using _super_t_::unlock;
        void lock() {
            while (false==try_lock()) {/**/ }
        }
    };
    mutable light_mutex _m_ReadWriteMutex;
public:
    NetworkCookieJar(QObject* /**/=nullptr);
    ~NetworkCookieJar();
public:
    QByteArray toByteArray();
    void fromByteArray(const QByteArray&);
public:
    virtual QList<QNetworkCookie> cookiesForUrl(const QUrl &url) const override;
    virtual bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList,const QUrl &url) override;
    virtual bool insertCookie(const QNetworkCookie &cookie) override;
    virtual bool updateCookie(const QNetworkCookie &cookie) override;
    virtual bool deleteCookie(const QNetworkCookie &cookie) override;
    using QNetworkCookieJar::allCookies;
private:
    CPLUSPLUS_OBJECT(NetworkCookieJar)
};

//#define DEBUG_BAIDUUSERNETWORKACCESSMANAGER
class _PrivateBaiduUserNetworkAccessManager : public QNetworkAccessManager {
    Q_OBJECT
private:
    QObjectsWatcher * const $m$thisWatcher;
    using _Super=QNetworkAccessManager;
public:
    _PrivateBaiduUserNetworkAccessManager(QObjectsWatcher *);
    QObjectsWatcher * getWatcher() const { return $m$thisWatcher; }
    QJSEngine * getJSEngine() const { return &$m$jsEngine; }
    NetworkCookieJar *cookieJar() const {
        return static_cast<NetworkCookieJar *>(_Super::cookieJar());
    }
    ~_PrivateBaiduUserNetworkAccessManager();
protected:
    QNetworkReply *createRequest(Operation,const QNetworkRequest &,QIODevice *) override;
    mutable QJSEngine $m$jsEngine;
#ifdef DEBUG_BAIDUUSERNETWORKACCESSMANAGER
    std::atomic<int> $m$replyCount={0};
#endif
private:
    CPLUSPLUS_OBJECT(_PrivateBaiduUserNetworkAccessManager)
};

class _PrivateBaiduUser :public BaiduPrivateBasic {
public:
    _PrivateBaiduUser();
    virtual ~_PrivateBaiduUser();

    void construct(std::shared_ptr<QSingleThreadPool> &&,BaiduUser *);

    using NetworkAccessManager=_PrivateBaiduUserNetworkAccessManager;
   
    /*线程共享数据*/
    class ExternData {
    public:
        std::shared_ptr<QObjectsWatcher> $m$watcherNetworkAccessManager;
        std::shared_ptr<QSingleThreadPool> $m$threadPool;
        NetworkAccessManager * $m$networkAccessManager=nullptr;
        void createNetworkAccessManager();
    };

    std::shared_ptr<ExternData> $m$externData;
    /*线程独占数据*/
    BaiduUser::BaiduUserState $m$state=BaiduUser::BaiduUserState::StateNone;
    QByteArray $m$gid/*gid*/;
    QByteArray $m$token/*token*/;
    QByteArray $m$vertifyCodeString/*验证码ID*/;
    std::atomic<bool> $m$isLogin={false};
    bool $m$isBaiduAsked=false;
private:
    CPLUSPLUS_OBJECT(_PrivateBaiduUser)
};

}/*baidu*/

#endif // _PRIVATEBAIDUUSER_HPP



