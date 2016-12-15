#include <cassert>
#include "BaiduUser.hpp"
#include <QtCore/qthread.h>
#include <QtCore/qobject.h>
#include "_PrivateBaiduUser.hpp"
#include <QtNetwork/qnetworkreply.h>
#include "_PrivateBaiduStaticData.hpp"
#include <QtNetwork/qnetworkrequest.h>

namespace baidu {

namespace {

inline void clear_data(QNetworkReply *reply) {
    reply->close();
}

}/*namespace*/

}/*baidu*/

namespace baidu {

BaiduUser::BaiduUser(
        std::shared_ptr<QSingleThreadPool> argSTP,
        QObject *p):_Super(p) {
    auto varThisPrivate=memory::make_shared<_PrivateBaiduUser>();
    $m$thisp=varThisPrivate;
    varThisPrivate->construct(std::move(argSTP),this);
}

BaiduUser::~BaiduUser() {

}

void _PrivateBaiduUser::construct(
        std::shared_ptr<QSingleThreadPool> &&arg,
        BaiduUser *) {
    $m$threadPool=std::move(arg);
    $m$watcherNetworkAccessManager=QObjectsWatcher::instance();
}

QNetworkReply *_PrivateBaiduUserNetworkAccessManager::createRequest(
        Operation a,
        const QNetworkRequest & b,
        QIODevice *c) {
    auto ans=_Super::createRequest(a,b,c);
    $m$thisWatcher->add(ans);
    return std::move(ans);
}

void _PrivateBaiduUser::createNetworkAccessManager() {
    if ($m$networkAccessManager) { return; }
    assert($m$threadPool->getQThread()==QThread::currentThread());
    $m$networkAccessManager=
        new NetworkAccessManager($m$watcherNetworkAccessManager.get());
    QObject::connect($m$watcherNetworkAccessManager.get(),
                      &QObjectsWatcher::finished,
                      $m$networkAccessManager,
                      &NetworkAccessManager::deleteLater,
                      Qt::QueuedConnection);
    $m$threadPool->addWatcher($m$networkAccessManager);
}

BaiduUser::BaiduUserState BaiduUser::getState()const {
    return getPrivateData()->$m$state;
}

void BaiduUser::setState(BaiduUser::BaiduUserState arg) {
    auto varThisp=getPrivateData();
    if (arg==varThisp->$m$state) { return; }
    varThisp->$m$state=arg;
    stateChanged(static_cast<int>(arg));
}


}/*baidu*/

/************************************************************/
namespace baidu/*baidu*/ {

namespace {//
namespace _private_login {

class Login :
    public baidu::DoBaiduUserObject,
    public std::enable_shared_from_this<Login> {
public:
    QString $m$userName/*用户名*/;
    QString $m$passWordRaw/*密码明文*/;
    QString $m$errorString=getBaiduStaticData()->unknow_error/*错误值*/;
    QSingleThreadPool * $m$singleThreadPool=nullptr;
    std::weak_ptr<BaiduPrivateBasic> $m$superPrivate/*回调结构的观察者*/;

    inline std::shared_ptr<_PrivateBaiduUser> lock();
    inline void finished_success();
    inline void finished_error();
    inline void create_networkaccessmanager();
    inline void get_baidu_cookie();
    inline void get_baidu_login_cookie();
    inline void get_baidu_token();

    inline void do_next();

    enum State :int {
        state_create_networkaccessmanager,
        state_waiting,
        state_error,
        state_success,
        state_getbaidu_cookie,
        state_getbaidu_login_cookie,
        state_get_baidu_token,
    };
    State $m$state=state_create_networkaccessmanager;
    State $m$nextState=state_create_networkaccessmanager;
    bool $m$isFinishedCalled=false;

    ~Login() {
        if ($m$isFinishedCalled) { return; }
        finished_error();
    }

    class StateMachine {
        Login *$m$thisp;
    public:
        StateMachine(Login * arg,State s):$m$thisp(arg) {
            arg->$m$state=s;
            arg->$m$nextState=state_error;
        }

        void normal_return(State s) {
            $m$thisp->$m$nextState=s;
        }

        void error_return(const QString &e) {
            $m$thisp->$m$errorString=e;
            $m$thisp->$m$nextState=state_error;
        }

        ~StateMachine() {
            $m$thisp->do_next();
        }
    };

private:
    CPLUSPLUS_OBJECT(Login)
};

inline void Login::get_baidu_token() {
    StateMachine varStateMachine{ this,state_get_baidu_token };
    auto varUserPrivate=this->lock();
    if (!varUserPrivate) { return; }

}

/*the cookie has been set in cookiejar*/
inline void Login::get_baidu_login_cookie() try {
    StateMachine varStateMachine{ this,state_getbaidu_login_cookie };
    auto varUserPrivate=this->lock();
    if (!varUserPrivate) { return; }
    auto varSTD=getBaiduStaticData();
    QNetworkRequest varRequest{ varSTD->baidu_login_url };
    varRequest.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);
    auto networkAM=varUserPrivate->$m$networkAccessManager;
    auto varReply=networkAM->get(varRequest);
    networkAM->getWatcher()->add(varReply);
    varReply->connect(varReply,&QNetworkReply::finished,
        [var=this->shared_from_this(),varReply]() {
        try {
            varReply->deleteLater();
            StateMachine varStateMachine{ var.get(),state_getbaidu_login_cookie };
            if (varReply->error()!=QNetworkReply::NoError) {
                return varStateMachine.error_return(varReply->errorString());
            }
            clear_data(varReply);
            return varStateMachine.normal_return(state_get_baidu_token);
        }
        catch (...) {
            CPLUSPLUS_EXCEPTION(false);
        }
    });
    return varStateMachine.normal_return(state_waiting);
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

/*the cookie has been set in cookiejar*/
inline void Login::get_baidu_cookie() try {
    StateMachine varStateMachine{ this,state_getbaidu_cookie };
    auto varUserPrivate=this->lock();
    if (!varUserPrivate) { return; }
    auto varSTD=getBaiduStaticData();
    QNetworkRequest varRequest{ varSTD->baidu_url };
    varRequest.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);
    auto networkAM=varUserPrivate->$m$networkAccessManager;
    auto varReply=networkAM->get(varRequest);
    networkAM->getWatcher()->add(varReply);
    varReply->connect(varReply,&QNetworkReply::finished,
        [var=this->shared_from_this(),varReply]() {
        try {
            varReply->deleteLater();
            StateMachine varStateMachine{ var.get(),state_getbaidu_cookie };
            if (varReply->error()!=QNetworkReply::NoError) {
                return varStateMachine.error_return(varReply->errorString());
            }
            clear_data(varReply);
            return varStateMachine.normal_return(state_getbaidu_login_cookie);
        }
        catch (...) {
            CPLUSPLUS_EXCEPTION(false);
        }
    });
    return varStateMachine.normal_return(state_waiting);
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline std::shared_ptr<_PrivateBaiduUser> Login::lock() {
    if (QObjectsWatcher::isQAppQuited()) { return{}; }
    auto ans=$m$superPrivate.lock();
    if (ans) {
        return std::static_pointer_cast<_PrivateBaiduUser>(std::move(ans));
    }
    return{};
}

inline void Login::finished_success() {
    $m$isFinishedCalled=true;
    if ($m$superPrivate.expired()) { return; }
    this->finished(true,{});
}

inline void Login::finished_error() {
    $m$isFinishedCalled=true;
    if ($m$superPrivate.expired()) { return; }
    this->finished(false,$m$errorString);
}

/*尽量增加异步性，提高响应速度*/
inline void Login::do_next() try {
    auto varPrivateData=$m$superPrivate.lock();
    if (varPrivateData) {
        switch ($m$nextState) {
            case state_create_networkaccessmanager:return $m$singleThreadPool->runLambda(
                            [var=this->shared_from_this()](){var->create_networkaccessmanager(); });
            case state_waiting:break;
            case state_error:finished_error(); break;
            case state_success:finished_success(); break;
            case state_getbaidu_cookie:$m$singleThreadPool->runLambda(
                [var=this->shared_from_this()](){var->get_baidu_cookie(); });
            case state_getbaidu_login_cookie:$m$singleThreadPool->runLambda(
                [var=this->shared_from_this()](){var->get_baidu_login_cookie(); });
            case state_get_baidu_token:$m$singleThreadPool->runLambda(
                [var=this->shared_from_this()](){var->get_baidu_token(); });
        }
    }

}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline void Login::create_networkaccessmanager()try {
    StateMachine varStateMachine{ this,state_create_networkaccessmanager };
    auto varPrivateData=$m$superPrivate.lock();
    if (varPrivateData) {
        assert($m$singleThreadPool->getQThread()==QThread::currentThread());
        $m$singleThreadPool->runLambda([var=this->shared_from_this()](){
            StateMachine varStateMachine{ var.get(),state_create_networkaccessmanager };
            try {
                auto varPrivateData=var->lock();
                if (varPrivateData) {
                    varPrivateData->createNetworkAccessManager();
                    return varStateMachine.normal_return(state_getbaidu_cookie);
                }
            }
            catch (...) {
                CPLUSPLUS_EXCEPTION(false);
            }
        });
        return varStateMachine.normal_return(state_waiting);
    }
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

}/**/
}//


}/*baidu*/
/************************************************************/

namespace baidu {

void BaiduUser::login(const QString &argUserName,const QString &argPassWord) {

    /*改变状态机*/
    this->setState(BaiduUser::BaiduUserState::StateLogin);

    /*初始化登陆器*/
    auto varLogin=memory::make_shared<_private_login::Login>();
    varLogin->$m$userName=argUserName;
    varLogin->$m$passWordRaw=argPassWord;
    varLogin->$m$superPrivate=this->$m$thisp;
    varLogin->$m$singleThreadPool=getPrivateData()->$m$threadPool.get();

    /*连接信号槽*/
    connect(varLogin.get(),&DoBaiduUserObject::finished,
            this,[this](bool a,const QString &b) {
        this->setState(BaiduUser::BaiduUserState::StateNone);
        this->loginFinished(a,b);
    },Qt::QueuedConnection);

    /*开始登陆*/
    varLogin->do_next();
}

QByteArray BaiduUser::gid() {
    QByteArray ans{ 35,Qt::Uninitialized };

    constexpr const static char toHex0[]={
        '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    };

    constexpr const static char toHex1[]={
        '8','9','A','B','C','D','E','F','8','9','A','B','C','D','E','F',
    };

    class Array {
        char data[35];
    public:
        Array():data{
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15], '-',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            '-','4',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15], '-',
            toHex1[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],'-',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15]
        } {
        }
    };

    ::new(ans.data()) Array;

    return std::move(ans);
}

}/*baidu*/



