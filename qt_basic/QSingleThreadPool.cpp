#include <map>
#include <mutex>
#include <tuple>
#include <future>
#include <thread>
#include <shared_mutex>
#include <QtCore/QEvent>
#include <QtCore/qtimer.h>
#include <QtCore/qthread.h>
#include "cplusplus_basic.hpp"
#include <QtCore/qeventloop.h>
#include "QSingleThreadPool.hpp"
#include "QApplicationWatcher.hpp"
#include <QtCore/qcoreapplication.h>

namespace  {
namespace _current_threads {

class Data{
public:
    std::shared_timed_mutex mutex;
    std::map<std::thread::id,std::weak_ptr<QSingleThreadPool>> threads;
private:
    CPLUSPLUS_OBJECT(Data)
};

Data * getData(){
    static Data * data_=new Data;
    return data_;
}

void add(std::thread::id a,std::weak_ptr<QSingleThreadPool> b){
    auto data=getData();
    std::unique_lock<std::shared_timed_mutex> _lock_{ data->mutex };
    data->threads[a]=std::move(b);
}


void remove(std::thread::id a){
    auto data=getData();
    std::unique_lock<std::shared_timed_mutex> _lock_{ data->mutex };
    data->threads.erase(a);
}

std::weak_ptr<QSingleThreadPool> find(std::thread::id a){
    if( QObjectsWatcher::isQAppQuited() ){return {};}
    auto data=getData();
    std::shared_lock<std::shared_timed_mutex> _lock_{ data->mutex };
    auto var = data->threads.find(a);
    if(var==data->threads.end()){return {};}
    return var->second;
}

}
}

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

using _p_thread_data_t=std::tuple<
_ThreadObjectRunableEvent *,
std::thread::id
>;

}/*namespace*/


class QSingleThreadPool::_Thread : public QThread {
public:
    std::promise<_p_thread_data_t> * promise_;

    _Thread(std::promise<_p_thread_data_t> *arg)
        :promise_(arg){}

    void run(){
        try{
            _ThreadObjectRunableEvent _eventDispatcher;

            /**/
            promise_->set_value( std::make_tuple(
                                     &_eventDispatcher,
                                     std::this_thread::get_id() ) );
            promise_=nullptr;
            /**/

            this->exec();
        }catch(...){}

    }
private:
    CPLUSPLUS_OBJECT(_RunableEvent)
};


namespace  {

std::atomic< QObject * > staticDelateLaterObject  ;

}/*namespace*/

namespace  {

/*QThread delete before main may be a bug*/
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

QSingleThreadPool::QSingleThreadPool(const private_construct &){

}

QSingleThreadPool::QSingleThreadPool(QObject *p):QObject(p){
    watcher_=QObjectsWatcher::instance();

    std::promise< _p_thread_data_t > varPromise;
    auto varThread = new _Thread(   &varPromise );

    connect(varThread,&QThread::finished,
            [varThread](){toDeleteQThread(varThread);});

    varThread->start();

    /*get thread data*/
    auto varThreadData=varPromise.get_future().get();
    this->thread_object_=std::get<0>(varThreadData);
    auto varThreadID=std::get<1>(varThreadData);

    this->children_=memory::make_shared<QSingleThreadPool>(private_construct{});
    this->children_->watcher_=this->watcher_;
    this->children_->thread_object_=this->thread_object_;

    _current_threads::add(varThreadID,this->children_);

    connect(watcher_.get(),
            &QObjectsWatcher::finished,
            varThread,
            [varThread,varThreadID](){
        _current_threads::remove( varThreadID );
        varThread->quit();
    });

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


namespace qappwatcher{

_ThreadObjectRunableEvent * qapp_events_loop;
std::shared_ptr<QSingleThreadPool> qapp_thread_pool;

void beginConstructQApplication(){
    staticDelateLaterObject.store( new _ThreadObjectRunableEvent );
    getMutex()->lock();
    assert(qapp_events_loop==nullptr);
    qapp_events_loop=new _ThreadObjectRunableEvent;
    qapp_thread_pool=
            memory::make_shared<QSingleThreadPool>(QSingleThreadPool::private_construct{});
    qapp_thread_pool->thread_object_=qapp_events_loop;
    qapp_thread_pool->watcher_=QObjectsWatcher::instance(false);
    _current_threads::add(std::this_thread::get_id(),qapp_thread_pool);
}

void endConstructQApplication(){
    getMutex()->unlock();
}

void beginDestructQApplication(){
    getMutex()->lock();
    qapp_thread_pool.reset();
    _current_threads::remove(std::this_thread::get_id());
}

void endDestructQApplication(){
    getMutex()->unlock();
}

}/*qappwatcher*/

std::weak_ptr<QSingleThreadPool> QSingleThreadPool::currentQSingleThreadPool(){
    return _current_threads::find(std::this_thread::get_id());
}
