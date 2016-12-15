#ifndef _PRIVATEBAIDUUSER_HPP
#define _PRIVATEBAIDUUSER_HPP

#include "BaiduUser.hpp"
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>
#include <QtNetwork/qnetworkaccessmanager.h>

namespace baidu {

class BaiduUser;

class _PrivateBaiduUserNetworkAccessManager : public QNetworkAccessManager {
    Q_OBJECT
private:
    QObjectsWatcher * const $m$thisWatcher;
    using _Super=QNetworkAccessManager;
public:
    _PrivateBaiduUserNetworkAccessManager(QObjectsWatcher *);
    QObjectsWatcher * getWatcher() const { return $m$thisWatcher; }
protected:
    QNetworkReply *createRequest(Operation,const QNetworkRequest &, QIODevice *) override;

private:
    CPLUSPLUS_OBJECT(_PrivateBaiduUserNetworkAccessManager)
};

class _PrivateBaiduUser :public BaiduPrivateBasic {
public:
    _PrivateBaiduUser();
    virtual ~_PrivateBaiduUser();

    void construct(std::shared_ptr<QSingleThreadPool> &&,BaiduUser *);
    void createNetworkAccessManager();

    using NetworkAccessManager=_PrivateBaiduUserNetworkAccessManager;
    std::shared_ptr<QObjectsWatcher> $m$watcherNetworkAccessManager;
    std::shared_ptr<QSingleThreadPool> $m$threadPool;
    NetworkAccessManager * $m$networkAccessManager=nullptr;
    BaiduUser::BaiduUserState $m$state=BaiduUser::BaiduUserState::StateNone;

private:
    CPLUSPLUS_OBJECT(_PrivateBaiduUser)
};

}/*baidu*/

#endif // _PRIVATEBAIDUUSER_HPP



