#ifndef QObjectsWatcher_HPP_0x99872
#define QObjectsWatcher_HPP_0x99872

#include <memory>
#include <QtCore/qobject.h>
#include <QtCore/qeventloop.h>
#include "qt_basic_global.hpp"

class _PrivateQObjectsWatcher;
class QT_BASICSHARED_EXPORT QObjectsWatcher final:
protected QObject,
public std::enable_shared_from_this<QObjectsWatcher>{
Q_OBJECT
protected:
    QObjectsWatcher(QObject * /**/=nullptr);
    ~QObjectsWatcher();
public:
    static bool isQAppQuited();
    static std::shared_ptr<QObjectsWatcher> instance(bool isLockQApp=false);
    static std::shared_ptr<QObjectsWatcher> lock(std::weak_ptr<QObjectsWatcher>&);
public:
    QObjectsWatcher(QObjectsWatcher &&)=delete;
    QObjectsWatcher(const QObjectsWatcher &)=delete;
    QObjectsWatcher&operator=(QObjectsWatcher &&)=delete;
    QObjectsWatcher&operator=(const QObjectsWatcher &)=delete;
public:
    std::weak_ptr<QObjectsWatcher> weakPointer()const { return _pm_this; }
    Q_SLOT void add(QObject *)/*thread safe*/;
    Q_SLOT void remove(QObject *)/*thread safe*/;
    Q_SIGNAL void finished();
protected:
    Q_SLOT void quit()/*thread safe*/;
    bool isOnFinishedDelete()const;
    void setOnFinishedDelete(bool=true);
protected:
    std::weak_ptr<QObjectsWatcher> _pm_this;
    std::shared_ptr<QEventLoopLocker> _pm_qt_app_lock;
    _PrivateQObjectsWatcher * _pm_data;
    _PrivateQObjectsWatcher * pData() { return _pm_data; }
    const _PrivateQObjectsWatcher * pData()const { return _pm_data; }
    friend class _PrivateQObjectsWatcher;
    static std::shared_ptr<QObjectsWatcher> _p_instance();
private:
    CPLUSPLUS_OBJECT(QObjectsWatcher)
};

#endif // QObjectsWatcher_HPP
