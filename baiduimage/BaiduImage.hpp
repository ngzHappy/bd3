#ifndef BAIDUIMAGE_HPP
#define BAIDUIMAGE_HPP

#include <QtCore/qvector.h>
#include <QtCore/qobject.h>
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>

namespace baidu {

class BaiduImage : public QObject {
    Q_OBJECT
public:
    class Item {
        using _t_int=std::int32_t;
    public:
        _t_int index;
        QString imageName;
        QByteArray imageUrl;
    };

    inline void setData(QVector<std::shared_ptr<Item>> &&);
    inline void setData(const QVector<std::shared_ptr<Item>> &);
    inline const QVector<std::shared_ptr<Item>>&getData()const;

public:
    Q_SIGNAL void finished(bool,const QString &);
private:
    QVector<std::shared_ptr<Item>> $m$data;
private:
    CPLUSPLUS_OBJECT(BaiduImage)
};

inline void BaiduImage::setData(QVector<std::shared_ptr<Item>> &&a) {
    $m$data=std::move(a);
}

inline void BaiduImage::setData(const QVector<std::shared_ptr<Item>> &a) {
    $m$data=a;
}

inline auto BaiduImage::getData()const->const QVector<std::shared_ptr<Item>>& {
    return $m$data;
}

}/*baidu*/

#endif // BAIDUIMAGE_HPP




