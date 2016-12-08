#include <cassert>
#include "QObjectsWatcher.hpp"
#include "_PrivateQObjectsWatcher.hpp"

QObjectsWatcher::QObjectsWatcher(QObject *arg):QObject(arg) {
    _pm_data=new _PrivateQObjectsWatcher(this);
}

QObjectsWatcher::~QObjectsWatcher() {
    delete _pm_data;
}

_PrivateQObjectsWatcher::_PrivateQObjectsWatcher(QObjectsWatcher *s):super(s){
    objectItemsMutex=memory::make_shared<std::mutex>();
    this->add(super);
}

_PrivateQObjectsWatcher::~_PrivateQObjectsWatcher() {

}

void _PrivateQObjectsWatcher::do_quit() {
    isQuit=true;
    super->finished();

    if (isDeleteOnFinished) {
        delete super;
    }
}

void _PrivateQObjectsWatcher::quit() {
    if (isQuit) { return; }
    auto && varLock=getObjectItemsLock();
    if (isQuit) { return; }
    isQuit=true;

    objectItems.erase(objectItems.find(super));

    /*really quit*/
    if (objectItems.empty()==true) {
        do_quit();
    }

    (void)varLock;
}

void _PrivateQObjectsWatcher::add(QObject *arg) {
    if (arg==nullptr) { return; }

    auto && varLock=getObjectItemsLock();

    if (isQuit) {
        assert("this is a logical error"&&false);
        delete arg;
        return;
    }

    if (objectItems.count(arg)>0) { return; }
    objectItems.emplace(arg,
                        connect(arg,&QObject::destroyed,
                                this,&_PrivateQObjectsWatcher::remove));
    (void)varLock;
}

void _PrivateQObjectsWatcher::remove(QObject *arg) {
    if (arg==nullptr) { return; }
    auto && varLock=getObjectItemsLock();
    auto pos=objectItems.find(arg);
    if (pos==objectItems.end()) { return; }
    this->disconnect(pos->connectData);
    objectItems.erase(pos);

    /*really quit*/
    if ((isQuit)&&(objectItems.empty()==true)) {
        do_quit();
    }

    (void)varLock;
}

void QObjectsWatcher::quit() {
    pData()->quit();
}

void QObjectsWatcher::add(QObject *arg) {
    pData()->add(arg);
}

void QObjectsWatcher::remove(QObject *arg) {
    pData()->remove(arg);
}

bool QObjectsWatcher::isOnFinishedDelete()const {
    return pData()->isDeleteOnFinished;
}

void QObjectsWatcher::setOnFinishedDelete(bool arg) {
    pData()->isDeleteOnFinished=arg;
}

/*End Of The File.*/
