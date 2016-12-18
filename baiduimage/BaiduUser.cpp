#include <cassert>
#include <text/gzip.hpp>
#include "BaiduUser.hpp"
#include <QtGui/qimage.h>
#include <QtCore/qthread.h>
#include <QtCore/qobject.h>
#include "_PrivateBaiduUser.hpp"
#include <QtNetwork/qnetworkreply.h>
#include "_PrivateBaiduStaticData.hpp"
#include <QtNetwork/qnetworkrequest.h>

//#define BAIDUUSER_DEBUG
#if defined(BAIDUUSER_DEBUG)
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
                      const QString & argVertifyCode) {

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

/***
w: 'a',
k: 'b',
v: 'c',
1: 'd',
j: 'e',
u: 'f',
2: 'g',
i: 'h',
t: 'i',
3: 'j',
h: 'k',
s: 'l',
4: 'm',
g: 'n',
5: 'o',
r: 'p',
q: 'q',
6: 'r',
f: 's',
p: 't',
7: 'u',
e: 'v',
o: 'w',
8: '1',
d: '2',
n: '3',
9: '4',
c: '5',
m: '6',
0: '7',
b: '8',
l: '9',
a: '0',

_z2C$q   :
_z&e3B   '
AzdH3F  /

***/

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

}/*_private_baidu_image*/
}/*namespace*/

std::pair<char*,char *> BaiduUser::uncompressBaiduImageUrl(char*a,const char *const b) {
    return _private_baidu_image::uncompress_baidu_image(a,b);
}

}/*baidu*/

