#ifndef QSINGLETHREADPOOL_HPP
#define QSINGLETHREADPOOL_HPP

#include <functional>
#include <QtCore/qobject.h>
#include "QObjectsWatcher.hpp"

class QT_BASICSHARED_EXPORT QSingleThreadPool :public QObject {
Q_OBJECT
public:
    QSingleThreadPool(QObject *);
    ~QSingleThreadPool();

    void run(void(*)(void));
    void run(void(*)(void*),void *);
    void run(void(*)(const void*),const void *);
    void run(void(*)(const std::shared_ptr<void>&),std::shared_ptr<void>);
    void run(void(*)(const std::shared_ptr<const void>&),std::shared_ptr<const void>);
    void runStdFunction(std::function<void(void)>);

    class Runable{
    protected:
        virtual void do_run() = 0;
    public:
        virtual ~Runable()=default;
    };

    void addWatcher(QObject *);
    void removeWatcher(QObject *);
    std::shared_ptr<QObjectsWatcher> getWatcher()const{ return watcher_; }

private:
    std::shared_ptr<QObjectsWatcher> watcher_;
    QObject * thread_object_;
    class _Thread;
private:
    CPLUSPLUS_OBJECT(QSingleThreadPool)
};

Q_DECLARE_METATYPE(std::shared_ptr<void>)

#endif // QSINGLETHREADPOOL_HPP
