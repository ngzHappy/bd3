#include <cassert>
#include <text/gzip.hpp>
#include "BaiduUser.hpp"
#include "BaiduImage.hpp"
#include <QtGui/qimage.h>
#include <QtCore/qthread.h>
#include <QtCore/qobject.h>
#include "_PrivateBaiduUser.hpp"
#include <QtNetwork/qnetworkreply.h>
#include "_PrivateBaiduStaticData.hpp"
#include <QtNetwork/qnetworkrequest.h>

#include <QtCore/qjsonarray.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsondocument.h>

//#define BAIDUUSER_DEBUG
#if defined(BAIDUUSER_DEBUG)
#include <QtCore/qdebug.h>
#endif

#define BAIDU_IMAGE_DEBUG
#if defined(BAIDU_IMAGE_DEBUG)
#include <fstream>
#include <QtCore/qdebug.h>
#endif

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
    $m$externData=memory::make_shared<ExternData>();
    $m$externData->$m$threadPool=std::move(arg);
    $m$externData->$m$watcherNetworkAccessManager=QObjectsWatcher::instance();
}

QNetworkReply *_PrivateBaiduUserNetworkAccessManager::createRequest(
        Operation a,
        const QNetworkRequest & b,
        QIODevice *c) {
    auto ans=_Super::createRequest(a,b,c);
    $m$thisWatcher->add(ans);
    return std::move(ans);
}

void _PrivateBaiduUser::ExternData::createNetworkAccessManager() {
    if ($m$networkAccessManager) { return; }
    assert($m$threadPool->getQThread()==QThread::currentThread());
    auto watcher=$m$watcherNetworkAccessManager.get();
    $m$networkAccessManager=new NetworkAccessManager(watcher);
    QObject::connect(watcher,
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

class StaticData_postLogin;
class Login :
    public baidu::DoBaiduUserObject,
    public std::enable_shared_from_this<Login> {
public:
    /*input output*/
    class ExternAns {
    public:
        QByteArray $m$gid;
        QByteArray $m$token;
        QByteArray $m$rsaPublikKey;
        QByteArray $m$rsaKeyIndex;
        QByteArray $m$passWord;
        QByteArray $m$verifycode;
        QByteArray $m$codestring;
        QByteArray $m$verifycode_url;
        QImage $m$verifycode_image;
        bool $m$isBaiduAsked;
    };
    std::shared_ptr<ExternAns> $m$externAns;
    /*input*/
    QString $m$userName/*用户名*/;
    QString $m$passWordRaw/*密码明文*/;
    QSingleThreadPool * $m$singleThreadPool=nullptr;
    _PrivateBaiduUserNetworkAccessManager * $m$networkAccessManager=nullptr;
    std::weak_ptr<BaiduPrivateBasic> $m$superPrivate/*回调结构的观察者*/;
    std::shared_ptr<_PrivateBaiduUser::ExternData> $m$superExternData/*来自父对象的线程共享数据*/;
    /*output by signal*/
    QString $m$errorString=getBaiduStaticData()->unknow_error/*错误值*/;

    inline bool expired() const;
    inline void finished_success();
    inline void finished_error();
    inline void finished_verifycode();
    inline void create_networkaccessmanager();
    inline void get_baidu_cookie();
    inline void get_baidu_login_cookie();
    inline void get_baidu_token();
    inline void get_rsa_key();
    inline void encrypt_RSA();
    inline void post_login();
    inline void post_login_finished(QNetworkReply *,const StaticData_postLogin*);
    inline void get_verifycode_image();

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
        state_encrypt_RSA,
        state_post_login,
        state_get_verifycode_image,
        state_verifycode,
    };

    inline static QLatin1String state_to_string(State);

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
#if defined(BAIDUUSER_DEBUG)
            qDebug()<<state_to_string(s);
#endif
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

        Login * operator->() { return $m$thisp; }
        const Login * operator->() const { return $m$thisp; }
    };

private:
    CPLUSPLUS_OBJECT(Login)
};

QLatin1String Login::state_to_string(State state) {
    switch (state) {
        case Login::state_create_networkaccessmanager: return u8R"///(state_create_networkaccessmanager)///"_qls;
        case Login::state_waiting: return u8R"///(state_waiting)///"_qls;
        case Login::state_error: return u8R"///(state_error)///"_qls;
        case Login::state_success: return u8R"///(state_success)///"_qls;
        case Login::state_getbaidu_cookie: return u8R"///(state_getbaidu_cookie)///"_qls;
        case Login::state_getbaidu_login_cookie: return u8R"///(state_getbaidu_login_cookie)///"_qls;
        case Login::state_get_baidu_token: return u8R"///(state_get_baidu_token)///"_qls;
        case Login::state_get_rsa_key: return u8R"///(state_get_rsa_key)///"_qls;
        case Login::state_encrypt_RSA: return u8R"///(state_encrypt_RSA)///"_qls;
        case Login::state_post_login: return u8R"///(state_post_login)///"_qls;
        case Login::state_get_verifycode_image: return u8R"///(state_get_verifycode_image)///"_qls;
        case Login::state_verifycode: return u8R"///(state_verifycode)///"_qls;
    }
    return u8R"///(unknow)///"_qls;
}

class StaticData_postLogin final {
public:
    const QUrl url;
    const std::regex error_no_regex{ u8R"r(err_no=([0-9]+))r" };
    const std::regex code_string_regex{ u8R"r(codeString=([^&]+))r" };
    const std::regex vcodetype_regex{ u8R"r(vcodetype=([^&]+))r" };
    const QByteArray code_string_url{ "https://passport.baidu.com/cgi-bin/genimage?"_qba };
    const QByteArray key_Accept{ "Accept"_qba };
    const QByteArray value_Accept{ "text/html, application/xhtml+xml, */*"_qba };
    const QByteArray key_Referer{ "Referer"_qba };
    const QByteArray value_Referer{ "https://www.baidu.com/"_qba };
    const QByteArray key_Accept_Language{ "Accept-Language"_qba };
    const QByteArray value_Accept_Language{ "zh-CN"_qba };
    const QByteArray key_User_Agent{ "User-Agent"_qba };
    const QByteArray key_Content_Type{ "Content-Type"_qba };
    const QByteArray value_Content_Type{ "application/x-www-form-urlencoded"_qba };
    const QByteArray key_Accept_Encoding{ "Accept-Encoding"_qba };
    const QByteArray value_Accept_Encoding{ "gzip, deflate"_qba };
    const std::map<int,QString,std::less<>,memory::Allocator<int>> error_code=[]() {
        std::map<int,QString,std::less<>,memory::Allocator<int>> ans{
            { -1	    ,u8"系统错误,请您稍后再试"_qstr },
            { 1	        ,u8"您输入的帐号格式不正确"_qstr },
            { 2	        ,u8"您输入的帐号不存在"_qstr },
            { 3	        ,u8"验证码不存在或已过期,请重新输入"_qstr },
            { 4	        ,u8"您输入的帐号或密码有误"_qstr },
            { 5	        ,u8"请在弹出的窗口操作,或重新登录"_qstr },
            { 6	        ,u8"您输入的验证码有误"_qstr },
            { 7	        ,u8"密码错误"_qstr },
            { 16	    ,u8"您的帐号因安全问题已被限制登录"_qstr },
            { 257	    ,u8"请输入验证码"_qstr },
            { 100027	,u8"百度正在进行系统升级，暂时不能提供服务，敬请谅解"_qstr },
            { 400031	,u8"请在弹出的窗口操作,或重新登录"_qstr },
            { 401007	,u8"您的手机号关联了其他帐号，请选择登录"_qstr },
            { 120021	,u8"登录失败,请在弹出的窗口操作,或重新登录"_qstr },
            { 500010	,u8"登录过于频繁,请24小时后再试"_qstr },
            { 200010	,u8"验证码不存在或已过期"_qstr },
            { 100005	,u8"系统错误,请您稍后再试"_qstr },
            { 120019	,u8"请在弹出的窗口操作,或重新登录"_qstr },
            { 110024	,u8"此帐号暂未激活"_qstr },
            { 100023	,u8"开启Cookie之后才能登录"_qstr },
            { 17	    ,u8"您的帐号已锁定"_qstr },
            { 500002    ,u8"您输入的验证码有误"_qstr},
            { 500018    ,u8"验证码已失效，请重试"_qstr},
        };
        return std::move(ans);
    }();
public:
    StaticData_postLogin()
        :url("https://passport.baidu.com/v2/api/?login"_qls) {}
};

static memory::StaticData<StaticData_postLogin> staticData_postLogin;
inline void Login::post_login() try {
    StateMachine varStateMachine{ this,state_post_login };
    if (this->expired()) { return; }

    auto varSTD=getBaiduStaticData();
    static memory::StaticPointer<StaticData_postLogin>
        varPsd{ staticData_postLogin };
    auto & externData=*($m$externAns);

    const static constexpr char staticPage[]={ "https%3A%2F%2Fwww.baidu.com%2Fcache%2Fuser%2Fhtml%2Fv3Jump.html" };
    const static constexpr char u[]={ "https%3A%2F%2Fwww.baidu.com%2F" };
    const static constexpr char splogin[]={ "rate" };
    const static constexpr char logLoginType[]={ "pc_loginDialog" };
    const static constexpr char safeflg[]={ "0" };
    const static constexpr char detect[]={ "1" };
    const static constexpr char quick_user[]={ "0" };
    const static constexpr char memberPass[]={ "on" };
    const static constexpr char loginType[]={ "dialogLogin" };
    const static constexpr char loginmerge[]={ "true" };

    QByteArray varPostData;
    {
        /*当前时间戳*/
        const auto tt=BaiduUser::currentTime();
        /*用户名*/
        const QByteArray varUserName=$m$userName
            .toUtf8()
            .toPercentEncoding();
        /*一个随机数*/
        const auto ppui_logintime=
            QByteArray::number(9900+(std::rand()&511));
        /*构建临时对象缓存数据*/
        const auto varTmpPostData=cat_to_url(
                    "staticpage",staticPage,
                    "charset","utf-8",
                    "token",externData.$m$token,
                    "tpl","mn",
                    "subpro","",
                    "apiver","v3",
                    "tt",tt,
                    "codestring",externData.$m$codestring/*验证码id*/,
                    "safeflg",safeflg,
                    "u",u,
                    "isPhone","false",
                    "detect",detect,
                    "gid",externData.$m$gid,
                    "quick_user",quick_user,
                    "logintype",loginType,
                    "logLoginType",logLoginType,
                    "idc","",
                    "loginmerge",loginmerge,
                    "splogin",splogin,
                    "username",varUserName,
                    "password",externData.$m$passWord,
                    "verifycode",externData.$m$verifycode/*验证码*/,
                    "mem_pass",memberPass,
                    "rsakey",externData.$m$rsaKeyIndex,
                    "crypttype","12",
                    "ppui_logintime",ppui_logintime,
                    "countrycode","",
                    "callback","parent.bd__pcbs__s09032"
        );

        auto varPostSize=static_cast<int>(varTmpPostData.size())-1;
        varPostData.reserve(varPostSize+4);
        /*去掉第一个&*/
        varPostData.append(varTmpPostData.data()+1,
                           varPostSize);
    }

    QNetworkRequest req(varPsd->url);
    req.setRawHeader(varPsd->key_Accept,varPsd->value_Accept);
    req.setRawHeader(varPsd->key_Referer,varPsd->value_Referer);
    req.setRawHeader(varPsd->key_Accept_Language,varPsd->value_Accept_Language);
    req.setRawHeader(varPsd->key_User_Agent,varSTD->userAgent);
    req.setRawHeader(varPsd->key_Content_Type,varPsd->value_Content_Type);
    req.setRawHeader(varPsd->key_Accept_Encoding,varPsd->value_Accept_Encoding);

    auto networkAM=this->$m$networkAccessManager;
    auto varReply=networkAM->post(req,varPostData);

    varReply->connect(varReply,&QNetworkReply::finished,
                      [var=this->shared_from_this(),varReply,
                      varPsd=varPsd.pointer()]() {
        var->post_login_finished(varReply,varPsd);
    });

    return varStateMachine.normal_return(state_waiting);
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

class PostLoginJSParserAns {
public:
    bool isOk=false;
    int errorCode=0;
    QString errorString;
    QByteArray VertifyCodeID;
    QByteArray VertifyCodeUrl;
    QByteArray vcodetype;
};

static void parserPostLoginJS(
        const gumbo::string&varJS,
        const StaticData_postLogin*varPSD,
        PostLoginJSParserAns*varAns
) {
    int varErrorNO=0;
    do {
        std::cmatch error_no;
        if (std::regex_search(
            varJS.c_str(),varJS.c_str()+varJS.size(),
            error_no,varPSD->error_no_regex)) {
            varErrorNO=std::atoi(error_no[1].first);
            varAns->errorCode=varErrorNO;
            if (varErrorNO!=0) {

                if (varErrorNO==257) {
                    /*https://passport.baidu.com/cgi-bin/genimage?*/
                    /*codeString=([^&]+)*/
                    std::cmatch code_string;
                    if (std::regex_search(varJS.c_str(),varJS.c_str()+varJS.size(),
                        code_string,varPSD->code_string_regex)) {
                        varAns->VertifyCodeID=QByteArray(code_string[1].first,
                                static_cast<int>(code_string[1].length()));
                        varAns->VertifyCodeUrl=varPSD->code_string_url
                            +varAns->VertifyCodeID;
                        if (std::regex_search(varJS.c_str(),varJS.c_str()+varJS.size(),
                            code_string,varPSD->vcodetype_regex)) {
                            auto varTmp=QByteArray(code_string[1].first,
                                    static_cast<int>(code_string[1].length()));
#ifndef NDEBUG
                            QJSEngine test_eng;
                            auto check_test=test_eng.evaluate(u8R"(")"+varTmp+u8R"(")").toString();
#endif

                            varAns->vcodetype=varTmp.replace(u8R"(\/)",2,u8R"(/)",1)
                                .toPercentEncoding();
#ifndef NDEBUG
                            assert(check_test.toUtf8().toPercentEncoding()
                                   ==varAns->vcodetype);
#endif
                        }
                        varAns->errorString=u8"请输入验证码"_qstr;
                        return;
                    }
                }

                if (varErrorNO==18) {
                    varAns->isOk=true/*要求手机验证码*/;
                    break;
                }

                auto it=varPSD->error_code.find(varErrorNO);
                if (it==varPSD->error_code.end()) {

                }
                else {
                    varAns->errorString=it->second;
                    return;
                }

            }
            else {
                varAns->isOk=true;
            }
        }
        else {
            varAns->errorString="can not find err_no="_qls;
            return;
        }
    } while (false);

}

inline void Login::post_login_finished(QNetworkReply *varReply,
                                       const StaticData_postLogin*varPsd) try {
    varReply->deleteLater();
    StateMachine varStateMachine{ this,state_post_login };

    if (this->expired()) { return; }

    auto varReplyData=varReply->readAll();

    {/*获得json*/
        if (varReplyData.isEmpty()) {
            return varStateMachine.error_return(varReply->errorString());
        }

        /*解压gzip*/
        if (qAsConst(varReplyData)[0]==char(0x001F)) {
            varReplyData=text::ungzip(varReplyData.cbegin(),varReplyData.cend());
        }

        clear_data(varReply);
    }

    auto varTmpJson=
        gumbo::getAllJavaScript(varReplyData.cbegin(),varReplyData.cend());

    if (varTmpJson.empty()) {
        return varStateMachine.error_return(u8R"///(can not find json)///"_qls);
    }

    const auto &varJS=*varTmpJson.begin();
    PostLoginJSParserAns varAns;
    parserPostLoginJS(varJS,varPsd,&varAns);

    if (varAns.VertifyCodeUrl.isEmpty()==false) {
        /*需要验证码*/
        auto & externAns=*$m$externAns;
        externAns.$m$codestring=std::move(varAns.VertifyCodeID);
        externAns.$m$verifycode_url=std::move(varAns.VertifyCodeUrl);
        return varStateMachine.normal_return(state_get_verifycode_image);
    }
    else {
        if (varAns.isOk==false) {
            /*登陆失败*/
            return varStateMachine.error_return(varAns.errorString);
        }
    }

    /*登陆成功*/
    auto networkAM=this->$m$networkAccessManager;
    auto varSD=getBaiduStaticData();

    {/*登陆百度图片，获得cookie，不必等待返回*/
        auto varReply=networkAM->get(QNetworkRequest(QUrl(varSD->baidu_image)));
        varReply->connect(varReply,&QNetworkReply::finished,
                          varReply,&QObject::deleteLater);
    }

    return varStateMachine.normal_return(state_success);

}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline void Login::encrypt_RSA() try {
    StateMachine varStateMachine{ this,state_encrypt_RSA };
    if (expired()) { return; }

    using Botan::byte;
    using Botan::Public_Key;
    using Botan::PK_Encryptor_EME;

    const auto & pemData=this->$m$externAns->$m$rsaPublikKey;
    auto varSTD=getBaiduStaticData();

    Botan::MemoryVector<byte> pem((const byte *)pemData.data(),pemData.size());
    std::unique_ptr<Public_Key> publicKey{ Botan::X509::load_key(pem) };
    Botan::AutoSeeded_RNG rng;
    PK_Encryptor_EME en(*publicKey,varSTD->EME_PKCS1_v1_5);
    const auto varPassWord=this->$m$passWordRaw.toUtf8();
    auto ans=en.encrypt((const byte*)varPassWord.data(),
                        varPassWord.size(),rng);

    if (ans.size()<1) {
        return varStateMachine.error_return(u8R"///(encrypt is null)///"_qls);
    }

    auto & passWord=this->$m$externAns->$m$passWord;
    passWord=QByteArray((char *)ans.begin(),static_cast<int>(ans.size()));

    passWord=passWord.toBase64();
    passWord=passWord.toPercentEncoding();

    return varStateMachine.normal_return(state_post_login);

}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline void Login::get_rsa_key() try {
    StateMachine varStateMachine{ this,state_get_rsa_key };
    if (this->expired()) { return; }
    auto varSTD=getBaiduStaticData();
    QUrl varURL;
    {
        const auto & gid=this->$m$externAns->$m$gid;
        const auto & token=this->$m$externAns->$m$token;
        const auto && tt=BaiduUser::currentTime();

        auto urlData=cat_to_url(
                    "tpl","mn",
                    "apiver","v3",
                    "tt",tt,
                    "class","login",
                    "gid",gid,
                    "callback","bd__cbs__dmwxux");

        QByteArray varTmpUrl;
        varTmpUrl.reserve(4
                          +varSTD->baidu_rsa_url.size()
                          +token.size()
                          +static_cast<int>(urlData.size()));
        varTmpUrl.append(varSTD->baidu_rsa_url);
        varTmpUrl.append(token);
        varTmpUrl.append(urlData.c_str(),static_cast<int>(urlData.size()));
        varURL.setUrl(varTmpUrl);
    }

    QNetworkRequest req(varURL);
    req.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);
    req.setRawHeader(varSTD->key_cccept_encoding,varSTD->gzip_deflate);

    auto networkAM=this->$m$networkAccessManager;
    auto varReply=networkAM->get(req);

    varReply->connect(varReply,&QNetworkReply::finished,
                      [var=this->shared_from_this(),varReply]() {
        try {
            varReply->deleteLater();
            StateMachine varStateMachine{ var.get(),state_get_rsa_key };
            if (var->expired()) { return; }
            auto varSTD=getBaiduStaticData();

            auto varJson=varReply->readAll();

            {/*获得json*/
                if (varJson.isEmpty()) {
                    return varStateMachine.error_return(varReply->errorString());
                }

                /*解压gzip*/
                if (qAsConst(varJson)[0]==char(0x001F)) {
                    varJson=text::ungzip(varJson.cbegin(),varJson.cend());
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

            auto networkAM=var->$m$networkAccessManager;
            auto jsEngine=networkAM->getJSEngine();

            {
                const auto json=jsEngine->evaluate("var bd__cbs__dmwxux = "_qls+varJson);

                if (json.isError()) {
                    return varStateMachine.error_return(json.toString());
                }

                const auto error=jsEngine->evaluate(u8R"(bd__cbs__dmwxux["errno"])"_qls);
                if (error.isError()) {
                    return varStateMachine.error_return(error.toString());
                }
                const auto pubkey=jsEngine->evaluate(u8R"(bd__cbs__dmwxux["pubkey"])"_qls);
                if (pubkey.isError()) {
                    return varStateMachine.error_return(pubkey.toString());
                }
                const auto key=jsEngine->evaluate(u8R"(bd__cbs__dmwxux["key"])"_qls);
                if (key.isError()) {
                    return varStateMachine.error_return(key.toString());
                }

                if (error.toString()==varSTD->zero) {
                    auto & vpubkey=var->$m$externAns->$m$rsaPublikKey;
                    auto & vkey=var->$m$externAns->$m$rsaKeyIndex;

                    vpubkey=pubkey.toString().toUtf8();
                    vkey=key.toString().toUtf8();

                    if (vkey.isEmpty()||vpubkey.isEmpty()) {
                        return varStateMachine.error_return(u8R"///(can not find pubkey)///"_qls);
                    }

                }
                else {
                    return varStateMachine.error_return(error.toString());
                }

            }

            return varStateMachine.normal_return(state_encrypt_RSA);

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

inline void Login::get_baidu_token() try {
    StateMachine varStateMachine{ this,state_get_baidu_token };
    if (this->expired()) { return; }
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

    auto networkAM=this->$m$networkAccessManager;
    QNetworkRequest varRequest(varUrl);
    varRequest.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);

    auto varReply=networkAM->get(varRequest);
    varReply->connect(varReply,&QNetworkReply::finished,
                      [var=this->shared_from_this(),varReply]() {
        varReply->deleteLater();
        StateMachine varStateMachine{ var.get(),state_get_baidu_token };
        try {
            if (var->expired()) { return; }

            auto varJson=varReply->readAll();

            {/*获得json*/
                if (varJson.isEmpty()) {
                    return varStateMachine.error_return(varReply->errorString());
                }

                /*解压gzip*/
                if (qAsConst(varJson)[0]==char(0x001F)) {
                    varJson=text::ungzip(varJson.cbegin(),varJson.cend());
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

            auto networkAM=var->$m$networkAccessManager;
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
    if (this->expired()) { return; }

    /*如果已经访问过www.baidu.com则跳过*/
    if (this->$m$externAns->$m$isBaiduAsked) {
        return varStateMachine.normal_return(state_get_baidu_token);
    }

    auto varSTD=getBaiduStaticData();
    QNetworkRequest varRequest{ varSTD->baidu_login_url };
    varRequest.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);
    auto networkAM=this->$m$networkAccessManager;
    auto varReply=networkAM->get(varRequest);
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
    if (this->expired()) { return; }
    auto varSTD=getBaiduStaticData();
    QNetworkRequest varRequest{ varSTD->baidu_url };
    varRequest.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);
    auto networkAM=this->$m$networkAccessManager;
    auto varReply=networkAM->get(varRequest);
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

inline bool Login::expired() const {
    if (QObjectsWatcher::isQAppQuited()) { return true; }
    return $m$superPrivate.expired();
}

inline void Login::finished_success() {
    $m$isFinishedCalled=true;
    if (this->expired()) { return; }
    this->finished(true,{},{});
}

inline void Login::finished_error() {
    $m$isFinishedCalled=true;
    if (this->expired()) { return; }
    this->finished(false,state_to_string($m$state)+
        (" : "_qls+$m$errorString),{});
}

inline void Login::finished_verifycode() {
    $m$isFinishedCalled=true;
    if (this->expired()) { return; }
    this->finished(false,u8R"///(请输入验证码)///"_qstr,
                   $m$externAns->$m$verifycode_image);
}

/*尽量增加异步性，提高响应速度*/
inline void Login::do_next() try {
    if (this->expired()) { return; }
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
        case state_encrypt_RSA:return $m$singleThreadPool->runLambda(
                        [var=this->shared_from_this()](){var->encrypt_RSA(); });
        case state_post_login:return $m$singleThreadPool->runLambda(
                        [var=this->shared_from_this()](){var->post_login(); });
        case state_get_verifycode_image:return $m$singleThreadPool->runLambda(
                        [var=this->shared_from_this()](){var->get_verifycode_image(); });
        case state_verifycode:finished_verifycode(); break;
    }

}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline void Login::create_networkaccessmanager()try {
    StateMachine varStateMachine{ this,state_create_networkaccessmanager };
    if (this->expired()) { return; }
    assert($m$singleThreadPool->getQThread()==QThread::currentThread());
    $m$singleThreadPool->runLambda([var=this->shared_from_this()](){
        StateMachine varStateMachine{ var.get(),state_create_networkaccessmanager };
        try {
            if (var->expired()) { return; }
            var->$m$superExternData->createNetworkAccessManager();
            var->$m$networkAccessManager=var->$m$superExternData->$m$networkAccessManager;
            return varStateMachine.normal_return(state_getbaidu_cookie);
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

inline void Login::get_verifycode_image()try {
    StateMachine varStateMachine{ this,state_get_verifycode_image };
    if (this->expired()) { return; }

    auto varSTD=getBaiduStaticData();
    const QUrl varUrl{ this->$m$externAns->$m$verifycode_url };
    QNetworkRequest varRequest{ varUrl };
    varRequest.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);

    auto networkAM=this->$m$networkAccessManager;
    auto varReply=networkAM->get(varRequest);
    varReply->connect(varReply,&QNetworkReply::finished,[
        var=this->shared_from_this(),varReply]() {
            try {
                varReply->deleteLater();
                StateMachine varStateMachine{ var.get(),state_get_verifycode_image };
                if (var->expired()) { return; }

                QImage varImage;
                {
                    auto varImageData=varReply->readAll();

                    if (varImageData.isEmpty()) {
                        return varStateMachine.error_return(u8R"///(获取验证码图像错误)///"_qstr);
                    }

                    /*解压gzip*/
                    if (qAsConst(varImageData)[0]==char(0x001F)) {
                        varImageData=text::ungzip(varImageData.cbegin(),
                                                  varImageData.cend());
                    }

                    varImage=QImage::fromData(varImageData);
                }

                if ((varImage.width()<1)||(varImage.height()<1)) {
                    return varStateMachine.error_return(u8R"///(获取验证码图像错误)///"_qstr);
                }

                var->$m$externAns->$m$verifycode_image=std::move(varImage);
                return varStateMachine.normal_return(state_verifycode);
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

}/**/
}//


}/*baidu*/
/************************************************************/

namespace baidu {

void BaiduUser::login(const QString &argUserName,
                      const QString &argPassWord,
                      const QString &argVertifyCode) {

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
    varLogin->$m$superExternData=getPrivateData()->$m$externData;
    varLogin->$m$userName=argUserName;
    varLogin->$m$passWordRaw=argPassWord;
    varLogin->$m$superPrivate=this->$m$thisp;
    varLogin->$m$singleThreadPool=getPrivateData()->$m$externData->$m$threadPool.get();
    varLogin->$m$externAns->$m$gid=thisp->$m$gid.isEmpty()?
        BaiduUser::gid():thisp->$m$gid;
    varLogin->$m$externAns->$m$isBaiduAsked=thisp->$m$isBaiduAsked;
    if (argVertifyCode.isEmpty()==false) {
        varLogin->$m$externAns->$m$verifycode=
            argVertifyCode.toUtf8().toPercentEncoding();
        varLogin->$m$externAns->$m$codestring=thisp->$m$vertifyCodeString;
    }

    /*连接信号槽*/
    /*同步更新数据*/
    connect(varLogin.get(),&DoBaiduUserObject::finished,
            this,[this,externAns=varLogin->$m$externAns](
        bool a,const QString &b,const QImage & c) {
        auto thisp=getPrivateData();
        thisp->$m$gid=externAns->$m$gid;
        thisp->$m$token=externAns->$m$token;
        thisp->$m$vertifyCodeString=externAns->$m$codestring;
        thisp->$m$isLogin=a;
        thisp->$m$isBaiduAsked=externAns->$m$isBaiduAsked;
        this->setState(BaiduUser::BaiduUserState::StateNone);
        this->loginFinished(a,b,c);
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

namespace baidu {
namespace {
namespace _private_baidu_image {

std::pair<char *,char *> uncompress_baidu_image(char * begin,const char * const end) {
    if (false==(end>begin)) { return{ nullptr,nullptr }; }

    constexpr static char baidu_image_uncompress_table[]={
        /*0*/static_cast<char>(0),
        /*1*/static_cast<char>(1),
        /*2*/static_cast<char>(2),
        /*3*/static_cast<char>(3),
        /*4*/static_cast<char>(4),
        /*5*/static_cast<char>(5),
        /*6*/static_cast<char>(6),
        /*7*/static_cast<char>(7),
        /*8*/static_cast<char>(8),
        /*9*/static_cast<char>(9),
        /*10*/static_cast<char>(10),
        /*11*/static_cast<char>(11),
        /*12*/static_cast<char>(12),
        /*13*/static_cast<char>(13),
        /*14*/static_cast<char>(14),
        /*15*/static_cast<char>(15),
        /*16*/static_cast<char>(16),
        /*17*/static_cast<char>(17),
        /*18*/static_cast<char>(18),
        /*19*/static_cast<char>(19),
        /*20*/static_cast<char>(20),
        /*21*/static_cast<char>(21),
        /*22*/static_cast<char>(22),
        /*23*/static_cast<char>(23),
        /*24*/static_cast<char>(24),
        /*25*/static_cast<char>(25),
        /*26*/static_cast<char>(26),
        /*27*/static_cast<char>(27),
        /*28*/static_cast<char>(28),
        /*29*/static_cast<char>(29),
        /*30*/static_cast<char>(30),
        /*31*/static_cast<char>(31),
        /*32*/static_cast<char>(32),
        /*33*/static_cast<char>(33),
        /*34*/static_cast<char>(34),
        /*35*/static_cast<char>(35),
        /*36*/static_cast<char>(36),
        /*37*/static_cast<char>(37),
        /*38*/static_cast<char>(38),
        /*39*/static_cast<char>(39),
        /*40*/static_cast<char>(40),
        /*41*/static_cast<char>(41),
        /*42*/static_cast<char>(42),
        /*43*/static_cast<char>(43),
        /*44*/static_cast<char>(44),
        /*45*/static_cast<char>(45),
        /*46*/static_cast<char>(46),
        /*47*/static_cast<char>(47),
        /*'0'*/static_cast<char>('7'),
        /*'1'*/static_cast<char>('d'),
        /*'2'*/static_cast<char>('g'),
        /*'3'*/static_cast<char>('j'),
        /*'4'*/static_cast<char>('m'),
        /*'5'*/static_cast<char>('o'),
        /*'6'*/static_cast<char>('r'),
        /*'7'*/static_cast<char>('u'),
        /*'8'*/static_cast<char>('1'),
        /*'9'*/static_cast<char>('4'),
        /*58*/static_cast<char>(58),
        /*59*/static_cast<char>(59),
        /*60*/static_cast<char>(60),
        /*61*/static_cast<char>(61),
        /*62*/static_cast<char>(62),
        /*63*/static_cast<char>(63),
        /*64*/static_cast<char>(64),
        /*65*/static_cast<char>(65),
        /*66*/static_cast<char>(66),
        /*67*/static_cast<char>(67),
        /*68*/static_cast<char>(68),
        /*69*/static_cast<char>(69),
        /*70*/static_cast<char>(70),
        /*71*/static_cast<char>(71),
        /*72*/static_cast<char>(72),
        /*73*/static_cast<char>(73),
        /*74*/static_cast<char>(74),
        /*75*/static_cast<char>(75),
        /*76*/static_cast<char>(76),
        /*77*/static_cast<char>(77),
        /*78*/static_cast<char>(78),
        /*79*/static_cast<char>(79),
        /*80*/static_cast<char>(80),
        /*81*/static_cast<char>(81),
        /*82*/static_cast<char>(82),
        /*83*/static_cast<char>(83),
        /*84*/static_cast<char>(84),
        /*85*/static_cast<char>(85),
        /*86*/static_cast<char>(86),
        /*87*/static_cast<char>(87),
        /*88*/static_cast<char>(88),
        /*89*/static_cast<char>(89),
        /*90*/static_cast<char>(90),
        /*91*/static_cast<char>(91),
        /*92*/static_cast<char>(92),
        /*93*/static_cast<char>(93),
        /*94*/static_cast<char>(94),
        /*95*/static_cast<char>(95),
        /*96*/static_cast<char>(96),
        /*'a'*/static_cast<char>('0'),
        /*'b'*/static_cast<char>('8'),
        /*'c'*/static_cast<char>('5'),
        /*'d'*/static_cast<char>('2'),
        /*'e'*/static_cast<char>('v'),
        /*'f'*/static_cast<char>('s'),
        /*'g'*/static_cast<char>('n'),
        /*'h'*/static_cast<char>('k'),
        /*'i'*/static_cast<char>('h'),
        /*'j'*/static_cast<char>('e'),
        /*'k'*/static_cast<char>('b'),
        /*'l'*/static_cast<char>('9'),
        /*'m'*/static_cast<char>('6'),
        /*'n'*/static_cast<char>('3'),
        /*'o'*/static_cast<char>('w'),
        /*'p'*/static_cast<char>('t'),
        /*'q'*/static_cast<char>('q'),
        /*'r'*/static_cast<char>('p'),
        /*'s'*/static_cast<char>('l'),
        /*'t'*/static_cast<char>('i'),
        /*'u'*/static_cast<char>('f'),
        /*'v'*/static_cast<char>('c'),
        /*'w'*/static_cast<char>('a'),
        /*120*/static_cast<char>(120),
        /*121*/static_cast<char>(121),
        /*122*/static_cast<char>(122),
        /*123*/static_cast<char>(123),
        /*124*/static_cast<char>(124),
        /*125*/static_cast<char>(125),
        /*126*/static_cast<char>(126),
        /*127*/static_cast<char>(127),
    };

#ifdef NDEBUG
#else
    for (auto varTest=begin; varTest<end; ++varTest) {
        assert((*varTest)<127);
        assert((*varTest)>0);
    }
#endif

    const char * const map_table=baidu_image_uncompress_table;
    char * const ans_begin=begin;
    char * read=begin;
    char * write=begin;

    if ((end-begin)>5) {
        char current_char;
        const char * const last_replace_multi=end-5;
        for (; read<last_replace_multi; ++write) {
            current_char=*read;
            if (current_char=='_') {
                begin=read;
                if (*(++begin)=='z') {
                    if (*(++begin)=='2') {
                        if (*(++begin)=='C') {
                            if (*(++begin)=='$') {
                                if (*(++begin)=='q') {
                                    *write=':';
                                    read+=6;
                                    continue;
                                }
                            }
                        }
                    }
                    else if (*begin=='&') {
                        if (*(++begin)=='e') {
                            if (*(++begin)=='3') {
                                if (*(++begin)=='B') {
                                    *write='.';
                                    read+=6;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
            else if (current_char=='A') {
                begin=read;
                if (*(++begin)=='z') {
                    if (*(++begin)=='d') {
                        if (*(++begin)=='H') {
                            if (*(++begin)=='3') {
                                if (*(++begin)=='F') {
                                    *write='/';
                                    read+=6;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
            *write=*(map_table+current_char);
            ++read;
        }
    }

    for (; read<end; ++write) {
        *write=*(map_table+(*read));
        ++read;
    }

    return{ ans_begin,write };

}

class DownLoadBaiduImage :
    public DoBaiduUserObject,
    public std::enable_shared_from_this<DownLoadBaiduImage> {
public:

    enum State {
        state_waiting,
        state_finished,
        state_error,
        state_start,
        state_downlod,
        state_download_set,
    };

    bool $m$isFinishedCalled=false;
    State $m$currentState=state_waiting;
    State $m$nextState=state_start;

    inline void do_next();

    std::weak_ptr<void> $m$parentWatcher;
    inline bool expired() const;

    std::shared_ptr<QObject> $m$callBack;
    std::shared_ptr<_PrivateBaiduUser::ExternData>$m$externSuperData;

    inline void finished_success();
    inline void finished_error();
    inline void start_download();
    inline void next_download();
    inline void next_download_set();

    class Item {
    public:
        std::int32_t image_index=0;
        containers::string object_url;
    private:
        CPLUSPLUS_OBJECT(Item)
    };

    class ItemLess {
        static inline bool _p_less(const containers::string &l,const containers::string &r) {
            /*同一个对象*/
            if (&l==&r) {
                return false;
            }
            /*比较大小*/
            {
                const auto varLS=l.size();
                const auto varRS=r.size();
                if (varLS<varRS) { return true; }
                if (varRS<varLS) { return false; }
            }
            /*比较值*/
            auto lb=l.begin();
            auto le=l.end();
            auto rb=r.begin();
            for (; lb!=le; ++lb,++rb) {
                const auto &varL=*lb;
                const auto &varR=*rb;
                if (varL<varR) { return true; }
                if (varR<varL) { return false; }
            }
            return false;
        }
    public:

        bool operator()(const Item&l,const Item &r)const {
            return _p_less(l.object_url,r.object_url);
        }

        bool operator()(const std::shared_ptr<Item>&l,const std::shared_ptr<Item>&r)const {
            return _p_less(l->object_url,r->object_url);
        }

        bool operator()(const Item&l,const std::shared_ptr<Item>&r)const {
            return _p_less(l.object_url,r->object_url);
        }

        bool operator()(const std::shared_ptr<Item>&l,const Item &r)const {
            return _p_less(l->object_url,r.object_url);
        }

        using  is_transparent=std::less<void>::is_transparent;
    };

    class ExternAns {
    public:
        bool $m$hasError=false;
        QString $m$errorString;
        containers::set<std::shared_ptr<Item>,ItemLess>$m$Items;
        QVector<std::shared_ptr<BaiduImage::Item>> $m$AnsItems;
    };
    std::shared_ptr<ExternAns> $m$externAns;

    inline DownLoadBaiduImage();
    inline ~DownLoadBaiduImage();

    class StateMachine {
        DownLoadBaiduImage * const $m$super;
    public:
        auto * operator->() { return $m$super; }
        const auto * operator->() const { return $m$super; }

        inline StateMachine(DownLoadBaiduImage *,State);
        inline ~StateMachine();

        inline void normal_return(State);
        inline void error_return(const QString &);

    };

    containers::list<QString> $m$imageSet;
    /*页面信息*/
    std::int32_t page_perpage=30;
    std::int32_t page_current=0;
    std::int32_t page_last_count=0;
    std::int32_t page_less_count=0;
    /**/
    int page_all_counts=(std::numeric_limits<int>::max)();
    /*图片信息*/
    QByteArray image_key_word;

    inline void update_data();
private:
    CPLUSPLUS_OBJECT(DownLoadBaiduImage)
};

inline bool DownLoadBaiduImage::expired() const {
    if (QObjectsWatcher::isQAppQuited()) { return true; }
    return $m$parentWatcher.expired();
}

inline DownLoadBaiduImage::StateMachine::StateMachine(
        DownLoadBaiduImage *a,State s):$m$super(a) {
    a->$m$currentState=s;
    a->$m$nextState=state_error;
}

inline DownLoadBaiduImage::~DownLoadBaiduImage() {
    if ($m$isFinishedCalled) { return; }
    if (this->expired()) { return; }
    this->finished_error();
}

inline DownLoadBaiduImage::StateMachine::~StateMachine() {
    $m$super->do_next();
}

inline void DownLoadBaiduImage::StateMachine::normal_return(State s) {
    $m$super->$m$nextState=s;
}

inline void DownLoadBaiduImage::StateMachine::error_return(const QString &a) {
    $m$super->$m$externAns->$m$errorString=a;
    $m$super->$m$nextState=state_error;
}

inline DownLoadBaiduImage::DownLoadBaiduImage() {
    $m$externAns=std::make_shared<ExternAns>();
}

inline void DownLoadBaiduImage::do_next() try {
    if (expired()) { return; }
    auto varTP=$m$externSuperData->$m$threadPool.get();
    switch ($m$nextState) {
        case state_waiting:break;
        case state_finished: finished_success(); break;
        case state_error: finished_error(); break;
        case state_start: varTP->runLambda([var=this->shared_from_this()]() {
            var->start_download();
        }); break;
        case state_downlod: varTP->runLambda([var=this->shared_from_this()]() {
            var->next_download();
        });  break;
    }

}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline void DownLoadBaiduImage::finished_success() {
    $m$isFinishedCalled=true;
    if (this->expired()) { return; }
    $m$externAns->$m$hasError=false;
    this->update_data();
    this->notify();
}

inline void DownLoadBaiduImage::finished_error() {
    $m$isFinishedCalled=true;
    if (this->expired()) { return; }
    $m$externAns->$m$hasError=true;
    this->update_data();
    this->notify();
}

inline void DownLoadBaiduImage::start_download() try {
    if ($m$externSuperData->$m$networkAccessManager==nullptr) {
        this->$m$externSuperData->createNetworkAccessManager();
    }
    return next_download();
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline void DownLoadBaiduImage::update_data() {
    auto & varItems=$m$externAns->$m$Items;
    auto & varAns=$m$externAns->$m$AnsItems;
    varAns.resize(static_cast<int>(varItems.size()));
    for (const auto & varI:varItems) {
        auto item=memory::make_shared<BaiduImage::Item>();
        {
            const auto & objurl=varI->object_url;
            item->imageUrl=QByteArray(objurl.c_str(),static_cast<int>(objurl.size()));
        }
        varAns[varI->image_index]=std::move(item);
    }
    varItems.clear();
}

/***
{
    "queryEnc":"%E7%BE%8E%E5%A5%B3",
    "queryExt":"美女",
    "listNum":33802,
    "displayNum":508118,
    "gsm":"1e00000000001e",
    "bdFmtDispNum":"约508,000",
    "bdSearchTime":"",
    "isNeedAsyncRequest":1,
    "bdIsClustered":"1",
    "data":[
        {
            "adType":"0",
            "hasAspData":"0",
            "thumbURL":"http://f.hiphotos.baidu.com/image/h%3D360/sign=ba4bbbdf1b30e924d0a49a377c096e66/242dd42a2834349bbe78c852cdea15ce37d3beef.jpg",
            "middleURL":"http://f.hiphotos.baidu.com/image/h%3D200/sign=236c94ef2c381f3081198aa999004c67/242dd42a2834349bbe78c852cdea15ce37d3beef.jpg",
            "largeTnImageUrl":"",
            "hasLarge" :0,
            "hoverURL":"http://f.hiphotos.baidu.com/image/h%3D360/sign=ba4bbbdf1b30e924d0a49a377c096e66/242dd42a2834349bbe78c852cdea15ce37d3beef.jpg",
            "pageNum":0,
            "objURL":"ippr_z2C$qAzdH3FAzdH3Fu_z&e3Bitri5p5f_z&e3Bkwt17_z&e3Bv54AzdH3Ft4w2jAzdH3FrtvAzdH3Ftpj4AzdH3Fd9d119dwdbn9n9lkkj0bvbcdv1jw8cvjn01nkjju_z&e3B3r2",
            "fromURL":"ippr_z2C$qAzdH3FAzdH3Fooo_z&e3B99ln_z&e3Bv54AzdH3Fxtg22wg45pjAzdH3Fdab00AzdH3F8_z&e3Bip4",
            "fromURLHost":"www.4493.com",
            "currentIndex":"",
            "width":900,
            "height":563,
            "type":"",
            "filesize":"",
            "bdSrcType":"-1",
            "di":"0",
            "pi": "21065057213",
            "is":"0,36080",
            "hasThumbData":"0",
            "bdSetImgNum":15,
            "spn":0,
            "bdImgnewsDate":"1970-01-01 08:00",
            "fromPageTitle":"",
            "fromPageTitleEnc":"",
            "bdSourceName":"",
            "bdFromPageTitlePrefix":"",
            "isAspDianjing":0,
            "token":"",
            "imgType" : "",
            "cs" : "3178635078,662413851",
            "os" : "",
            "simid" : "",
            "personalized":"0",
            "simid_info":null,
            "face_info":null,
            "xiangshi_info":null,
            "adPicId":"0",
            "source_type":""
        },
***/

/*数出从左到右连续1的个数*/
static inline int left_1_count(unsigned char i) {
    constexpr static int map_table[]={
        /*0000'0000*/0,
        /*0000'0001*/0,
        /*0000'0010*/0,
        /*0000'0011*/0,
        /*0000'0100*/0,
        /*0000'0101*/0,
        /*0000'0110*/0,
        /*0000'0111*/0,
        /*0000'1000*/0,
        /*0000'1001*/0,
        /*0000'1010*/0,
        /*0000'1011*/0,
        /*0000'1100*/0,
        /*0000'1101*/0,
        /*0000'1110*/0,
        /*0000'1111*/0,
        /*0001'0000*/0,
        /*0001'0001*/0,
        /*0001'0010*/0,
        /*0001'0011*/0,
        /*0001'0100*/0,
        /*0001'0101*/0,
        /*0001'0110*/0,
        /*0001'0111*/0,
        /*0001'1000*/0,
        /*0001'1001*/0,
        /*0001'1010*/0,
        /*0001'1011*/0,
        /*0001'1100*/0,
        /*0001'1101*/0,
        /*0001'1110*/0,
        /*0001'1111*/0,
        /*0010'0000*/0,
        /*0010'0001*/0,
        /*0010'0010*/0,
        /*0010'0011*/0,
        /*0010'0100*/0,
        /*0010'0101*/0,
        /*0010'0110*/0,
        /*0010'0111*/0,
        /*0010'1000*/0,
        /*0010'1001*/0,
        /*0010'1010*/0,
        /*0010'1011*/0,
        /*0010'1100*/0,
        /*0010'1101*/0,
        /*0010'1110*/0,
        /*0010'1111*/0,
        /*0011'0000*/0,
        /*0011'0001*/0,
        /*0011'0010*/0,
        /*0011'0011*/0,
        /*0011'0100*/0,
        /*0011'0101*/0,
        /*0011'0110*/0,
        /*0011'0111*/0,
        /*0011'1000*/0,
        /*0011'1001*/0,
        /*0011'1010*/0,
        /*0011'1011*/0,
        /*0011'1100*/0,
        /*0011'1101*/0,
        /*0011'1110*/0,
        /*0011'1111*/0,
        /*0100'0000*/0,
        /*0100'0001*/0,
        /*0100'0010*/0,
        /*0100'0011*/0,
        /*0100'0100*/0,
        /*0100'0101*/0,
        /*0100'0110*/0,
        /*0100'0111*/0,
        /*0100'1000*/0,
        /*0100'1001*/0,
        /*0100'1010*/0,
        /*0100'1011*/0,
        /*0100'1100*/0,
        /*0100'1101*/0,
        /*0100'1110*/0,
        /*0100'1111*/0,
        /*0101'0000*/0,
        /*0101'0001*/0,
        /*0101'0010*/0,
        /*0101'0011*/0,
        /*0101'0100*/0,
        /*0101'0101*/0,
        /*0101'0110*/0,
        /*0101'0111*/0,
        /*0101'1000*/0,
        /*0101'1001*/0,
        /*0101'1010*/0,
        /*0101'1011*/0,
        /*0101'1100*/0,
        /*0101'1101*/0,
        /*0101'1110*/0,
        /*0101'1111*/0,
        /*0110'0000*/0,
        /*0110'0001*/0,
        /*0110'0010*/0,
        /*0110'0011*/0,
        /*0110'0100*/0,
        /*0110'0101*/0,
        /*0110'0110*/0,
        /*0110'0111*/0,
        /*0110'1000*/0,
        /*0110'1001*/0,
        /*0110'1010*/0,
        /*0110'1011*/0,
        /*0110'1100*/0,
        /*0110'1101*/0,
        /*0110'1110*/0,
        /*0110'1111*/0,
        /*0111'0000*/0,
        /*0111'0001*/0,
        /*0111'0010*/0,
        /*0111'0011*/0,
        /*0111'0100*/0,
        /*0111'0101*/0,
        /*0111'0110*/0,
        /*0111'0111*/0,
        /*0111'1000*/0,
        /*0111'1001*/0,
        /*0111'1010*/0,
        /*0111'1011*/0,
        /*0111'1100*/0,
        /*0111'1101*/0,
        /*0111'1110*/0,
        /*0111'1111*/0,
        /*1000'0000*/1,
        /*1000'0001*/1,
        /*1000'0010*/1,
        /*1000'0011*/1,
        /*1000'0100*/1,
        /*1000'0101*/1,
        /*1000'0110*/1,
        /*1000'0111*/1,
        /*1000'1000*/1,
        /*1000'1001*/1,
        /*1000'1010*/1,
        /*1000'1011*/1,
        /*1000'1100*/1,
        /*1000'1101*/1,
        /*1000'1110*/1,
        /*1000'1111*/1,
        /*1001'0000*/1,
        /*1001'0001*/1,
        /*1001'0010*/1,
        /*1001'0011*/1,
        /*1001'0100*/1,
        /*1001'0101*/1,
        /*1001'0110*/1,
        /*1001'0111*/1,
        /*1001'1000*/1,
        /*1001'1001*/1,
        /*1001'1010*/1,
        /*1001'1011*/1,
        /*1001'1100*/1,
        /*1001'1101*/1,
        /*1001'1110*/1,
        /*1001'1111*/1,
        /*1010'0000*/1,
        /*1010'0001*/1,
        /*1010'0010*/1,
        /*1010'0011*/1,
        /*1010'0100*/1,
        /*1010'0101*/1,
        /*1010'0110*/1,
        /*1010'0111*/1,
        /*1010'1000*/1,
        /*1010'1001*/1,
        /*1010'1010*/1,
        /*1010'1011*/1,
        /*1010'1100*/1,
        /*1010'1101*/1,
        /*1010'1110*/1,
        /*1010'1111*/1,
        /*1011'0000*/1,
        /*1011'0001*/1,
        /*1011'0010*/1,
        /*1011'0011*/1,
        /*1011'0100*/1,
        /*1011'0101*/1,
        /*1011'0110*/1,
        /*1011'0111*/1,
        /*1011'1000*/1,
        /*1011'1001*/1,
        /*1011'1010*/1,
        /*1011'1011*/1,
        /*1011'1100*/1,
        /*1011'1101*/1,
        /*1011'1110*/1,
        /*1011'1111*/1,
        /*1100'0000*/2,
        /*1100'0001*/2,
        /*1100'0010*/2,
        /*1100'0011*/2,
        /*1100'0100*/2,
        /*1100'0101*/2,
        /*1100'0110*/2,
        /*1100'0111*/2,
        /*1100'1000*/2,
        /*1100'1001*/2,
        /*1100'1010*/2,
        /*1100'1011*/2,
        /*1100'1100*/2,
        /*1100'1101*/2,
        /*1100'1110*/2,
        /*1100'1111*/2,
        /*1101'0000*/2,
        /*1101'0001*/2,
        /*1101'0010*/2,
        /*1101'0011*/2,
        /*1101'0100*/2,
        /*1101'0101*/2,
        /*1101'0110*/2,
        /*1101'0111*/2,
        /*1101'1000*/2,
        /*1101'1001*/2,
        /*1101'1010*/2,
        /*1101'1011*/2,
        /*1101'1100*/2,
        /*1101'1101*/2,
        /*1101'1110*/2,
        /*1101'1111*/2,
        /*1110'0000*/3,
        /*1110'0001*/3,
        /*1110'0010*/3,
        /*1110'0011*/3,
        /*1110'0100*/3,
        /*1110'0101*/3,
        /*1110'0110*/3,
        /*1110'0111*/3,
        /*1110'1000*/3,
        /*1110'1001*/3,
        /*1110'1010*/3,
        /*1110'1011*/3,
        /*1110'1100*/3,
        /*1110'1101*/3,
        /*1110'1110*/3,
        /*1110'1111*/3,
        /*1111'0000*/4,
        /*1111'0001*/4,
        /*1111'0010*/4,
        /*1111'0011*/4,
        /*1111'0100*/4,
        /*1111'0101*/4,
        /*1111'0110*/4,
        /*1111'0111*/4,
        /*1111'1000*/5,
        /*1111'1001*/5,
        /*1111'1010*/5,
        /*1111'1011*/5,
        /*1111'1100*/6,
        /*1111'1101*/6,
        /*1111'1110*/7,
        /*1111'1111*/8,
    };
    return map_table[i];
}

/*移除非UTF8字符*/
/*
UTF-8 valid format list:
0xxxxxxx
110xxxxx 10xxxxxx
1110xxxx 10xxxxxx 10xxxxxx
11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
*/
void static inline remove_invalid_utf8(
        unsigned char * b,
        const unsigned char * const e) {
    constexpr unsigned char replace_char=' ';
    for (; b<e; ++b) {
        auto & current_char=*b;
        auto current_char_left_1=left_1_count(current_char);
        switch (current_char_left_1) {
            case 0:continue; break;
            case 1:current_char=replace_char; break;
            case 2: {
                const auto b1=b+1;
                if ((b1<e)&&(1==left_1_count(*b1))) {
                    b=b1; continue;
                }
                current_char=replace_char;
            } break;
            case 3: {
                const auto b1=b+1;
                const auto b2=b1+1;
                if ((b2<e)
                        &&(1==left_1_count(*b1))
                        &&(1==left_1_count(*b2))) {
                    b=b2;
                    continue;
                }
                current_char=replace_char;
            }break;
            case 4: {
                const auto b1=b+1;
                const auto b2=b1+1;
                const auto b3=b2+1;
                if ((b3<e)
                        &&(1==left_1_count(*b1))
                        &&(1==left_1_count(*b2))
                        &&(1==left_1_count(*b3))) {
                    b=b3;
                    continue;
                }
                current_char=replace_char;
            }break;
            case 5: {
                const auto b1=b+1;
                const auto b2=b1+1;
                const auto b3=b2+1;
                const auto b4=b3+1;
                if ((b4<e)
                        &&(1==left_1_count(*b1))
                        &&(1==left_1_count(*b2))
                        &&(1==left_1_count(*b3))
                        &&(1==left_1_count(*b4))) {
                    b=b4;
                    continue;
                }
                current_char=replace_char;
            }break;
            case 6: {
                const auto b1=b+1;
                const auto b2=b1+1;
                const auto b3=b2+1;
                const auto b4=b3+1;
                const auto b5=b4+1;
                if ((b5<e)
                        &&(1==left_1_count(*b1))
                        &&(1==left_1_count(*b2))
                        &&(1==left_1_count(*b3))
                        &&(1==left_1_count(*b4))
                        &&(1==left_1_count(*b5))) {
                    b=b5;
                    continue;
                }
                current_char=replace_char;
            }break;
            case 7: current_char=replace_char; break;
            case 8: current_char=replace_char; break;
        }
    }
}

void static inline remove_invalid_utf8(
        char * b,
        const char * const e) {
    return remove_invalid_utf8(reinterpret_cast<unsigned char*>(b),
                               reinterpret_cast<const unsigned char*const>(e));
}

static inline QByteArray force_to_utf8(const QByteArray & argInput) {
    auto arg=argInput;
    char *begin=arg.data();
    auto end=begin+arg.size();
    remove_invalid_utf8(begin,end);
    return std::move(arg);
}

static inline void parse_json(
        DownLoadBaiduImage::StateMachine & s,
        const QByteArray &argJsonInput) {
    const auto argJson=force_to_utf8(argJsonInput);
    QJsonParseError varJsonError;
    auto varJsonDocument=QJsonDocument::fromJson(argJson,&varJsonError);

    if (varJsonError.error!=QJsonParseError::NoError) {
#if defined(BAIDU_IMAGE_DEBUG)
        std::ofstream ofs("error_.js",std::ios::binary);
        ofs.write(argJson.constData(),argJson.size());
        qDebug()<<varJsonError.errorString()<<varJsonError.offset;
#endif
        return s.error_return(varJsonError.errorString());
    }

#if defined(BAIDU_IMAGE_DEBUG)
    {/*just for test*/
        static std::atomic<std::int32_t> indentedJsonIndex={ 0 };
        auto indentedJson=varJsonDocument.toJson();
        std::ofstream ofs(("js_test_"+
            QByteArray::number(++indentedJsonIndex)
            +"_.js").constData());
        ofs<<indentedJson.constData();
    }
#endif

    const auto varRootObject=varJsonDocument.object();
    QJsonArray varJsonArray;

    {/*遍历json*/
        auto rootB=varRootObject.constBegin();
        auto rootE=varRootObject.constEnd();

        for (auto varI=rootB; varI!=rootE; ++varI) {
            if (varI->isArray()&&(varI.key()=="data"_qls)) {
                varJsonArray=varI->toArray();
            }
            else {
                const auto varKey=varI.key();
                if (varKey=="listNum"_qls) {
                    s->page_all_counts=varI->toInt();
                }
                //else if (varKey=="queryEnc"_qls) {}
                //else if (varKey=="queryExt"_qls) {}
                //else if (varKey=="displayNum"_qls) {}
                //else if (varKey=="gsm"_qls) {}
                //else if (varKey=="bdFmtDispNum"_qls) {}
                //else if (varKey=="bdSearchTime"_qls) {}
                //else if (varKey=="isNeedAsyncRequest"_qls) {}
                //else if (varKey=="bdIsClustered"_qls) {}
            }
        }
    }

    if (varJsonArray.count()<2) {
        return s.normal_return(DownLoadBaiduImage::state_finished);
    }

    {/*遍历jsonarray*/
        for (const auto & varI:qAsConst(varJsonArray)) {
            if (varI.isObject()) {
                auto jsonObject=varI.toObject();
                auto cend=jsonObject.constEnd();
                auto item=memory::make_shared< DownLoadBaiduImage::Item >();

                do {/*"is": "0,0", "bdSetImgNum": 8, */
                    auto bdSetImgNum=jsonObject.constFind("bdSetImgNum"_qls);
                    if (bdSetImgNum==cend) { break; }
                    auto setNum=bdSetImgNum->toInt();
                    if (setNum<1) { break; }
                    auto varIs=jsonObject.constFind("is"_qls);
                    if (varIs==cend) { break; }
                    auto varIsValue=varIs->toString().trimmed();
                    if (varIsValue.isEmpty()) { break; }
                    s->$m$imageSet.push_back(std::move(varIsValue));
                } while (false);

                do {
                    auto objurl=jsonObject.constFind("objURL"_qls);
                    if (objurl==cend) { break; }
                    auto rawURL=objurl->toString().toUtf8();
                    auto plainURL=uncompress_baidu_image(const_cast<char*>(rawURL.constBegin()),
                                                         rawURL.constEnd());
                    item->object_url=containers::string(plainURL.first,plainURL.second);
                    if (item->object_url.empty()) { break; }
                    auto & items=s->$m$externAns->$m$Items;
                    item->image_index=static_cast<std::int32_t>(items.size());
                    items.insert(item);
                } while (false);

            }
        }
    }

    if (s->$m$imageSet.empty()) {
        return s.normal_return(DownLoadBaiduImage::state_downlod);
    }
    else {
        return s.normal_return(DownLoadBaiduImage::state_download_set);
    }

}

inline void DownLoadBaiduImage::next_download() try {

    if (expired()) { return; }

    StateMachine s(this,state_downlod);
    auto varSTD=getBaiduStaticData();

    QUrl varUrl;
    {
        const auto pn=QByteArray::number(s->page_current);
        const auto rn=QByteArray::number(s->page_perpage);
        const auto url_=cat_to_url(
                    /**/"ipn","rj",
                    /**/"ct","201326592",
                    /**/"is","",
                    /**/"fp","result",
                    /**/"queryWord",s->image_key_word,
                    /**/"cl","2",
                    /**/"lm","-1",
                    /**/"ie","utf-8",
                    /**/"oe","utf-8",
                    /**/"adpicid","",
                    /**/"st","-1",
                    /**/"z","",
                    /**/"ic","0",
                    /**/"word",s->image_key_word,
                    /**/"s","",
                    /**/"se","",
                    /**/"tab","",
                    /**/"width","",
                    /**/"height","",
                    /**/"face","0",
                    /**/"istype","2",
                    /**/"qc","",
                    /**/"nc","1",
                    /**/"fr","",
                    /**/"pn",pn,
                    /**/"rn",rn,
                    /**/"gsm","96",
                    /**/"1482041581410",""
        );
        s->page_current+=s->page_perpage;
        QByteArray url=varSTD->get_baidu_image_url;
        url.reserve(url.size()+static_cast<int>(url_.size())+4);
        url.append(url_.c_str(),static_cast<int>(url_.size()));
        varUrl.setUrl(url);
    }

    auto varNAM=$m$externSuperData->$m$networkAccessManager;
    QNetworkRequest varREQ(varUrl);
    varREQ.setRawHeader(varSTD->key_user_agent,varSTD->userAgent);
    varREQ.setRawHeader(varSTD->key_cccept_encoding,varSTD->gzip_deflate);

    auto varReply=varNAM->get(varREQ);

    connect(varReply,&QNetworkReply::finished,
            [varReply,var=this->shared_from_this()]() {
        varReply->deleteLater();
        try {
            StateMachine s(var.get(),state_downlod);
            if (s->expired()) { return; }

            QByteArray varJson=varReply->readAll();

            {/*获得json*/
                if (varJson.isEmpty()) {
                    return s.error_return(varReply->errorString());
                }

                /*解压gzip*/
                if (qAsConst(varJson)[0]==char(0x001F)) {
                    varJson=text::ungzip(varJson.cbegin(),varJson.cend());
                }

                if (varJson.isEmpty()) {
                    return s.error_return(varReply->errorString());
                }
                clear_data(varReply);
            }

            parse_json(s,varJson);

        }
        catch (...) {
            CPLUSPLUS_EXCEPTION(false);
        }
    });

    return s.normal_return(state_waiting);
}
catch (...) {
    CPLUSPLUS_EXCEPTION(false);
}

inline void DownLoadBaiduImage::next_download_set() try {
    if (expired()) { return; }

    StateMachine s(this,state_download_set);
    auto varSTD=getBaiduStaticData();




    return s.normal_return(state_waiting);
}
catch (...) { 
    CPLUSPLUS_EXCEPTION(false);
}

}/*_private_baidu_image*/
}/*namespace*/

void BaiduUser::downLoad(std::shared_ptr<BaiduImage> arg) {
    if (arg==nullptr) { return; }
    using T=_private_baidu_image::DownLoadBaiduImage;
    auto varImagesDownLoad=memory::make_shared<T>();

    auto thisp=this->getPrivateData();

    varImagesDownLoad->$m$callBack=arg;
    varImagesDownLoad->$m$externSuperData=thisp->$m$externData;
    varImagesDownLoad->$m$parentWatcher=$m$thisp;

    /*设置关键字*/
    varImagesDownLoad->image_key_word=
        arg->getKeyWord().toUtf8().toPercentEncoding();

    connect(varImagesDownLoad.get(),&T::notify,
            arg.get(),[arg,
            externAns=varImagesDownLoad->$m$externAns]() {

        if (externAns->$m$hasError) {
            arg->finished(false,externAns->$m$errorString);
        }
        else {
            arg->finished(true,{});
        }

    },Qt::QueuedConnection);

    return varImagesDownLoad->do_next();
}

std::pair<char*,char *> BaiduUser::uncompressBaiduImageUrl(char*a,const char *const b) {
    return _private_baidu_image::uncompress_baidu_image(a,b);
}

}/*baidu*/

