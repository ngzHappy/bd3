#include <future>
#include <QtCore/QEvent>
#include <QtCore/qtimer.h>
#include <QtCore/qthread.h>
#include "cplusplus_basic.hpp"
#include <QtCore/qeventloop.h>
#include "QSingleThreadPool.hpp"
#include <QtCore/qcoreapplication.h>

namespace  {

static auto eventType(){
    static auto ans= static_cast<QEvent::Type>(
                QEvent::registerEventType());
    return ans;
}

}/*namespace*/

QEvent::Type QSingleThreadPool::eventID(){
    return eventType();
}

namespace {

using _RunableEvent = QSingleThreadPool::RunableEvent;

class _ThreadObjectRunableEvent : public QObject {
public:
    bool event(QEvent *e) override{
        if( e->type() == eventType() ){
            static_cast< _RunableEvent * >( e )->run();
            return true;
        }
        return QObject::event(e);
    }
private:
    CPLUSPLUS_OBJECT(_RunableEvent)
};

}/*namespace*/


class QSingleThreadPool::_Thread : public QThread {
public:
    std::promise<_ThreadObjectRunableEvent * > * promise_;

    _Thread(std::promise<_ThreadObjectRunableEvent * > *arg)
        :promise_(arg){}

    void run(){
        _ThreadObjectRunableEvent _eventDispatcher;

        promise_->set_value( &_eventDispatcher );
        promise_=nullptr;

        this->exec();
    }
private:
    CPLUSPLUS_OBJECT(_RunableEvent)
};


namespace  {

std::atomic< QObject * > staticDelateLaterObject  ;

}/*namespace*/

static void _1_fun_on_qpp(){
    /*never deleted*/
    staticDelateLaterObject.store( new _ThreadObjectRunableEvent );
}

Q_COREAPP_STARTUP_FUNCTION(_1_fun_on_qpp)

namespace  {

/*QThread delete before main is a bug*/
static void toDeleteQThread(QThread *arg){

    if( staticDelateLaterObject.load()==nullptr ){
        return arg->deleteLater();
    }

    class Event :public _RunableEvent {
        void(*_fun)(QThread*);
        QThread * _data;
    public:
        Event(void(*f)(QThread*),QThread*d):_fun(f),_data(d){}
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };

    /*move to main thread and delete it*/
    QCoreApplication::postEvent(
                staticDelateLaterObject.load(),
                new Event([](QThread *arg){
                    QTimer::singleShot(10,staticDelateLaterObject.load(),
                    [arg](){delete arg;});
                },arg));

}

}/*namespace*/

QSingleThreadPool::QSingleThreadPool(QObject *p):QObject(p){
    watcher_=QObjectsWatcher::instance();

    std::promise<_ThreadObjectRunableEvent *> varPromise;
    auto varThread = new _Thread( &varPromise );

    connect(varThread,&QThread::finished,
            [varThread](){toDeleteQThread(varThread);});
    connect(watcher_.get(),&QObjectsWatcher::finished,
            varThread,&QThread::quit);

    varThread->start();
    thread_object_=varPromise.get_future().get();

}

QSingleThreadPool::~QSingleThreadPool(){

}

void QSingleThreadPool::run(void(*f)(void)){
    if(f==nullptr){return;}
    class Event :public _RunableEvent {
        void(*_fun)(void);
    public:
        Event(void(*f)(void)):_fun(f){}
        void do_run() override { _fun(); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    QCoreApplication::postEvent(thread_object_,new Event(f));
}

void QSingleThreadPool::run(void(*f)(void*),void *d){
    if(f==nullptr){return;}
    class Event :public _RunableEvent {
        void(*_fun)(void*);
        void * _data;
    public:
        Event(void(*f)(void*),void*d):_fun(f),_data(d){}
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    QCoreApplication::postEvent(thread_object_,new Event(f,d));
}

void QSingleThreadPool::run(void(*f)(const void*),const void *d){
    if(f==nullptr){return;}
    class Event :public _RunableEvent {
        void(*_fun)(const void*);
        const void * _data;
    public:
        Event(void(*f)(const void*),const void*d):_fun(f),_data(d){}
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    QCoreApplication::postEvent(thread_object_,new Event(f,d));
}

void QSingleThreadPool::run(
        void(*f)(const std::shared_ptr<void> &),
        std::shared_ptr<void> d){
    if(f==nullptr){return;}
    class Event :public _RunableEvent {
        void(*_fun)(const std::shared_ptr<void> &);
        std::shared_ptr<void> _data;
    public:
        Event(void(*f)(const std::shared_ptr<void>&),std::shared_ptr<void>&&d):
            _fun(f),
            _data(std::move(d)){}
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    QCoreApplication::postEvent(thread_object_,new Event(f,std::move(d)));
}

void QSingleThreadPool::run(
        void(*f)(const std::shared_ptr<const void> &),
        std::shared_ptr<const void> d){
    if(f==nullptr){return;}
    class Event :public _RunableEvent {
        void(*_fun)(const std::shared_ptr<const void> &);
        std::shared_ptr<const void> _data;
    public:
        Event(void(*f)(const std::shared_ptr<const void>&),std::shared_ptr<const void>&&d):
            _fun(f),
            _data(std::move(d)){}
        void do_run() override { _fun(_data); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    QCoreApplication::postEvent(thread_object_,new Event(f,std::move(d)));
}

void QSingleThreadPool::runStdFunction(std::function<void(void)> f) {
    if(bool(f)==false){return;}
    class Event :public _RunableEvent {
        std::function<void(void)> _fun;
    public:
        Event(std::function<void(void)>&&f):_fun(std::move(f)){}
        void do_run() override { _fun(); }
    private:
        CPLUSPLUS_OBJECT(Event)
    };
    QCoreApplication::postEvent(thread_object_,new Event(std::move(f)));
}

void QSingleThreadPool::addWatcher(QObject *arg){
    watcher_->add(arg);
}

void QSingleThreadPool::removeWatcher(QObject *arg){
    watcher_->remove(arg);
}

void QSingleThreadPool::_p_run(RunableEvent *arg){
    QCoreApplication::postEvent(thread_object_,arg);
}



