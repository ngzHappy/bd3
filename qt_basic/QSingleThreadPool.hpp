#ifndef QSINGLETHREADPOOL_HPP
#define QSINGLETHREADPOOL_HPP

#include <functional>
#include <type_traits>
#include <QtCore/QEvent>
#include <QtCore/qobject.h>
#include "QObjectsWatcher.hpp"
#include "QApplicationWatcher.hpp"

class QT_BASICSHARED_EXPORT QSingleThreadPool:public QObject{
Q_OBJECT
private:
    static QEvent::Type eventID();
    class private_construct{};
    friend void qappwatcher::beginConstructQApplication();
    friend void qappwatcher::endConstructQApplication();
    friend void qappwatcher::beginDestructQApplication();
    friend void qappwatcher::endDestructQApplication();
public:
    QSingleThreadPool(const private_construct &);
    QSingleThreadPool(QObject *);
    ~QSingleThreadPool();

    void run(void(*)(void));
    void run(void(*)(void*),void *);
    void run(void(*)(const void*),const void *);
    void run(void(*)(const std::shared_ptr<void>&),std::shared_ptr<void>);
    void run(void(*)(const std::shared_ptr<const void>&),std::shared_ptr<const void>);
    void runStdFunction(std::function<void(void)>);
    template<typename T>void runLambda(T &&);

    class Runable{
    protected:
        virtual void do_run() = 0;
    public:
        virtual ~Runable()=default;
    };

    class RunableEvent :
            public QEvent,
            public Runable {
    public:
        RunableEvent() :QEvent( eventID() ) {}
        inline void run(){
            try{ do_run(); }
            catch(...){CPLUSPLUS_EXCEPTION(false);}
        }
    };

    void addWatcher(QObject *);
    void removeWatcher(QObject *);
    std::shared_ptr<QObjectsWatcher> getWatcher()const{ return watcher_; }

    static std::weak_ptr<QSingleThreadPool> currentQSingleThreadPool();
private:
    std::shared_ptr<QObjectsWatcher> watcher_;
    std::shared_ptr<QSingleThreadPool> children_;
    QObject * thread_object_;
    class _Thread;
    void _p_run(RunableEvent *);
private:
    CPLUSPLUS_OBJECT(QSingleThreadPool)
};

template<typename T>
void QSingleThreadPool::runLambda(T && arg){
    using U=std::remove_cv_t<std::remove_reference_t<T>>;
    class _RunableEvent :public RunableEvent {
        U fun_;
    public:
        _RunableEvent(T &&arg):fun_(std::forward<T>(arg)){}
        void do_run()override{ fun_(); }
    private:
        CPLUSPLUS_OBJECT(_RunableEvent)
    };
    _p_run(new _RunableEvent(std::forward<T>(arg)));
}

Q_DECLARE_METATYPE(std::shared_ptr<void>)

#endif // QSINGLETHREADPOOL_HPP
