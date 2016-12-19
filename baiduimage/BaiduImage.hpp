#ifndef BAIDUIMAGE_HPP
#define BAIDUIMAGE_HPP

#include <QtCore/qvector.h>
#include <QtCore/qobject.h>
#include <QtBasicLibrary.hpp>
#include <cplusplus_basic.hpp>

namespace baidu {

class BaiduImage final : public QObject,
        public std::enable_shared_from_this<BaiduImage> {
    Q_OBJECT
public:
    class Item {
    public:
        QString imageName;
        QByteArray imageUrl;
    private:
        CPLUSPLUS_OBJECT(Item)
    };

    inline void setData(QVector<std::shared_ptr<Item>> &&);
    inline void setData(const QVector<std::shared_ptr<Item>> &);
    inline const QVector<std::shared_ptr<Item>>&getData()const;

    inline const QString & getKeyWord()const;
    inline void setKeyWord(const QString &);
    inline void setKeyWord(QString &&);

public:
    Q_SIGNAL void finished(bool,const QString &);
private:
    QVector<std::shared_ptr<Item>> $m$data;
    QString $m$keyword;
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

inline const QString & BaiduImage::getKeyWord()const {
    return $m$keyword;
}

inline void BaiduImage::setKeyWord(const QString &a) {
    $m$keyword=a;
}

inline void BaiduImage::setKeyWord(QString &&a) {
    $m$keyword=std::move(a);
}

}/*baidu*/

#endif // BAIDUIMAGE_HPP




