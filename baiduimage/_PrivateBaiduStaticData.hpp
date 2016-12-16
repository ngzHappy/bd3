#ifndef _PRIVATEBAIDUSTATICDATA_HPP
#define _PRIVATEBAIDUSTATICDATA_HPP

#ifdef __cplusplus

#include <regex>
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>
#include <cplusplus_basic.hpp>
#include <containers/string.hpp>

namespace  baidu {

static inline std::regex operator""_stdr(const char * a,std::size_t b) {
    return{ a,b };
}

static inline QString operator""_qstr(const char *a,std::size_t b) {
    return QString::fromUtf8(a,static_cast<int>(b));
}

static inline QByteArray operator""_qba(const char *a,std::size_t b) {
    return QByteArray{ a,static_cast<int>(b) };
}

static inline QLatin1String operator""_qls(const char *a,std::size_t b) {
    return QLatin1Literal(a,static_cast<int>(b));
}

using string=containers::string;

template<typename _T_>
class StringRef;

template<typename T,std::size_t N>
class StringRef<T[N]> {
    const T(&_m_Data)[N];
public:
    constexpr StringRef(const T(&argData)[N]):_m_Data(argData) {}
    constexpr const char * data() const { return _m_Data; }
    constexpr int size() const { return int(N-1); }
};

template<>
class StringRef<QByteArray> {
    const QByteArray & _m_Data;
public:
    constexpr StringRef(const QByteArray&arg):_m_Data(arg) {}
    const char *data() const { return _m_Data.data(); }
    int size() const { return _m_Data.size(); }
};

template<>
class StringRef<string> {
    const string & _m_Data;
public:
    constexpr StringRef(const string&arg):_m_Data(arg) {}
    const char *data() const { return _m_Data.data(); }
    int size() const { return _m_Data.size(); }
};

template<typename _T_>
constexpr auto make_string_ref(const _T_&arg) {
    return StringRef<_T_>(arg);
}

template<std::size_t N>
constexpr auto make_string_ref(const char(&arg)[N]) {
    return StringRef<char[N]>(arg);
}

namespace utility_cpp14 {
#include "_PrivateBaiDuUserCatToUrl.hpp"
}/*utility_cpp14*/

/* &a=b */
template<typename ..._T_>
string cat_to_url(const _T_&...arg) {
    return utility_cpp14::__cat_to_url(make_string_ref(arg)...);
}

class _PrivateBaiduStaticData {
public:
    _PrivateBaiduStaticData();
public:
    const containers::string EME_PKCS1_v1_5="EME-PKCS1-v1_5";
    const QByteArray gzip_deflate="gzip, deflate"_qba;
    const QByteArray key_cccept_encoding=u8R"///(Accept-Encoding)///"_qba;
    const QByteArray baidu_rsa_url=u8R"///(https://passport.baidu.com/v2/getpublickey?token=)///"_qba;
    const std::regex token_check=u8R"///([0-9a-zA-Z]+)///"_stdr;
    const QLatin1String zero="0"_qls;
    const QByteArray baidu_token_url=u8R"(https://passport.baidu.com/v2/api/?getapi)"_qba;
    const QString baidu_login_url="https://www.baidu.com/cache/user/html/login-1.2.html"_qstr;
    const QByteArray userAgent="Mozilla/5.0 (Windows NT 10.0; WOW64; rv:49.0) Gecko/20100101 Firefox/49.0"_qba;
    const QByteArray key_user_agent="User-Agent"_qba;
    const QString baidu_url="http://www.baidu.com"_qstr;
    const QString unknow_error="unknow error"_qstr;
private:
    CPLUSPLUS_OBJECT(_PrivateBaiduStaticData)
};

extern _PrivateBaiduStaticData *getBaiduStaticData();

}/*baidu*/

#endif //__cplusplus

#endif // _PRIVATEBAIDUSTATICDATA_HPP



