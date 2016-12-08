#ifndef QObjectsWatcher_HPP_0x99872
#define QObjectsWatcher_HPP_0x99872

#include <memory>
#include <QtCore/qobject.h>
#include "qt_basic_global.hpp"

class _PrivateQObjectsWatcher;
class QT_BASICSHARED_EXPORT QObjectsWatcher : public QObject {
    Q_OBJECT
public:
    QObjectsWatcher(QObject * /**/=nullptr);
    ~QObjectsWatcher();
public:
    QObjectsWatcher(QObjectsWatcher &&)=delete;
    QObjectsWatcher(const QObjectsWatcher &)=delete;
    QObjectsWatcher&operator=(QObjectsWatcher &&)=delete;
    QObjectsWatcher&operator=(const QObjectsWatcher &)=delete;
public:
    Q_SLOT void quit()/*thread safe*/;
    Q_SLOT void add(QObject *)/*thread safe*/;
    Q_SLOT void remove(QObject *)/*thread safe*/;
    Q_SIGNAL void finished();
public:
    bool isOnFinishedDelete()const;
    void setOnFinishedDelete(bool=true);
protected:
    _PrivateQObjectsWatcher * _pm_data;
    _PrivateQObjectsWatcher * pData() { return _pm_data; }
    const _PrivateQObjectsWatcher * pData()const { return _pm_data; }
private:
    CPLUSPLUS_OBJECT(QObjectsWatcher)
};

#endif // QObjectsWatcher_HPP
