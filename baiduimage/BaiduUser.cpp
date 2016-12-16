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
    /*input output*/
    class ExternAns {
    public:
        QByteArray $m$gid;
        QByteArray $m$token;
    };
    std::shared_ptr<ExternAns> $m$externAns;
    /*input*/
    QString $m$userName/*用户名*/;
    QString $m$passWordRaw/*密码明文*/;
    QSingleThreadPool * $m$singleThreadPool=nullptr;
    std::weak_ptr<BaiduPrivateBasic> $m$superPrivate/*回调结构的观察者*/;
    /*output by signal*/
    QString $m$errorString=getBaiduStaticData()->unknow_error/*错误值*/;

    inline std::shared_ptr<_PrivateBaiduUser> lock();
    inline void finished_success();
    inline void finished_error();
    inline void create_networkaccessmanager();
    inline void get_baidu_cookie();
    inline void get_baidu_login_cookie();
    inline void get_baidu_token();
    inline void get_rsa_key();

    inline void do_next();

    enum State :int {
        state_create_networkaccessmanager,
        state_waiting,
        state_error,
        state_success,
        state_getbaidu_cookie,
        state_getbaidu_login_cookie,
        state_get_baidu_token,
        state_get_rsa_key,
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

inline void Login::get_rsa_key() try{
    StateMachine varStateMachine{ this,state_get_rsa_key };
    auto varUserPrivate=this->lock();
    if (!varUserPrivate) { return; }
    
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline void Login::get_baidu_token() try {
    StateMachine varStateMachine{ this,state_get_baidu_token };
    auto varUserPrivate=this->lock();
    if (!varUserPrivate) { return; }
    auto varSTD=getBaiduStaticData();
    QUrl varUrl;
    {/*set url*/
        const auto && tt=BaiduUser::currentTime();
        const auto & gid=this->$m$externAns->$m$gid;
        const auto url_=cat_to_url(
            "tpl","mn",
            "apiver","v3",
            "tt",tt,
            "class","login",
            "gid",gid,
            "logintype","dialogLogin",
            "callback","bd__cbs__akwyzc"
        );
        QByteArray varTmpUrl;
        varTmpUrl.reserve(4
            +varSTD->baidu_token_url.size()
            +static_cast<int>(url_.size()));
        varTmpUrl.append(varSTD->baidu_token_url);
        varTmpUrl.append(url_.c_str(),static_cast<int>(url_.size()));
        varUrl.setUrl(varTmpUrl);
    }

    auto networkAM=varUserPrivate->$m$networkAccessManager;
    QNetworkRequest varRequest(varUrl);
    varRequest.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);

    auto varReply=networkAM->get(varRequest);
    networkAM->getWatcher()->add(varReply);

    varReply->connect(varReply,&QNetworkReply::finished,
        [var=this->shared_from_this(),varReply]() {
        varReply->deleteLater();
        StateMachine varStateMachine{ var.get(),state_get_baidu_token };
        try {
            auto varUserPrivate=var->lock();
            if (!varUserPrivate) { return; }

            auto varJson=varReply->readAll();

            {/*获得json*/
                if (varJson.isEmpty()) {
                    return varStateMachine.error_return(varReply->errorString());
                }

                /*remove ()*/
                varJson=varJson.mid(varJson.indexOf("("_qls)+1);
                if (varJson.isEmpty()) {
                    return varStateMachine.error_return(varReply->errorString());
                }
                varJson.resize(varJson.size()-1);

                if (varJson.isEmpty()) {
                    return varStateMachine.error_return(varReply->errorString());
                }
                clear_data(varReply);
            }

            auto networkAM=varUserPrivate->$m$networkAccessManager;
            auto jsEngine=networkAM->getJSEngine();

            {/*获得token*/
                auto ans=jsEngine->evaluate("var bd__cbs__89tioq = "_qls+varJson);
                if (ans.isError()) {
                    return varStateMachine.error_return(ans.toString());
                }
                auto error=jsEngine->evaluate(u8R"(bd__cbs__89tioq["errInfo"]["no"])"_qls);
                auto token=jsEngine->evaluate(u8R"(bd__cbs__89tioq["data"]["token"])"_qls);

                if (error.isError()) {
                    return varStateMachine.error_return(error.toString());
                }
                if (token.isError()) {
                    return varStateMachine.error_return(token.toString());
                }

                auto varSTD=getBaiduStaticData();
                if (error.toString()==varSTD->zero) {
                    auto & ansToken=var->$m$externAns->$m$token;
                    ansToken=token.toString().toUtf8();
                    if (ansToken.isEmpty()) {
                        return varStateMachine.error_return("find token is null!"_qls);
                    }

                    /*进一步检查token是否正确*/
                    if (false==std::regex_match(ansToken.cbegin(),
                        ansToken.cend(),
                        varSTD->token_check)) {
                        return varStateMachine.error_return("find token is not right!"_qls);
                    }

                }
                else {
                    return varStateMachine.error_return("can not find token!"_qls);
                }

            }

            return varStateMachine.normal_return(state_get_rsa_key);
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
            case state_getbaidu_cookie:return $m$singleThreadPool->runLambda(
                [var=this->shared_from_this()](){var->get_baidu_cookie(); });
            case state_getbaidu_login_cookie:return $m$singleThreadPool->runLambda(
                [var=this->shared_from_this()](){var->get_baidu_login_cookie(); });
            case state_get_baidu_token:return $m$singleThreadPool->runLambda(
                [var=this->shared_from_this()](){var->get_baidu_token(); });
            case state_get_rsa_key:return $m$singleThreadPool->runLambda(
                [var=this->shared_from_this()](){var->get_rsa_key(); });
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

    auto thisp=getPrivateData();
    {/*如果已经登陆，则退出；如果正在执行其他行为，则退出；*/
        if (thisp->$m$isLogin) { return; }
        if (thisp->$m$state!=BaiduUserState::StateNone) { return; }
    }

    /*改变状态机*/
    this->setState(BaiduUser::BaiduUserState::StateLogin);

    /*初始化登陆器*/
    auto varLogin=memory::make_shared<_private_login::Login>();
    varLogin->$m$externAns=memory::make_shared<_private_login::Login::ExternAns>();
    varLogin->$m$userName=argUserName;
    varLogin->$m$passWordRaw=argPassWord;
    varLogin->$m$superPrivate=this->$m$thisp;
    varLogin->$m$singleThreadPool=getPrivateData()->$m$threadPool.get();
    varLogin->$m$externAns->$m$gid=thisp->$m$gid.isEmpty()? 
        BaiduUser::gid():thisp->$m$gid;

    /*连接信号槽*/
    /*同步更新数据*/
    connect(varLogin.get(),&DoBaiduUserObject::finished,
            this,[this,externAns=varLogin->$m$externAns](bool a,const QString &b) {
        auto thisp=getPrivateData();
        thisp->$m$gid=externAns->$m$gid;
        thisp->$m$token=externAns->$m$token;
        thisp->$m$isLogin=a;
        this->setState(BaiduUser::BaiduUserState::StateNone);
        this->loginFinished(a,b);
    },Qt::QueuedConnection);

    /*开始登陆*/
    return varLogin->do_next();
}

bool BaiduUser::isLogin()const {
    return getPrivateData()->$m$isLogin;
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

QByteArray BaiduUser::currentTime() {
    return QByteArray::number(QDateTime::currentMSecsSinceEpoch());
}

}/*baidu*/



