﻿#ifndef QRUNONCE_HPP
#define QRUNONCE_HPP

#include <type_traits>
#include <QtCore/qobject.h>

namespace _private_QRunOnce_ {

template<typename T,bool=(std::is_base_of<QObject,T>::value)||
(std::is_pointer<T>::value&&std::is_convertible<T,QObject *>::value)>
class Item {
    Item(const Item &)=delete;
    Item&operator=(const Item &)=delete;
public:
    Item(QObject &o) { o.deleteLater(); }
    Item(QObject *o) { o->deleteLater(); }
    ~Item() {}

    Item&operator=(Item &&arg) {
        if (this==&arg) { return *this; }
        return *this;
    }

    Item(Item &&) {}
};

template<typename T>
class Item<T,false> {
    T * _xobject;
    Item(const Item &)=delete;
    Item&operator=(const Item &)=delete;
public:
    Item(T &o):_xobject(&o) {}
    ~Item() { if (_xobject) { _xobject->reset(); } }

    Item&operator=(Item &&arg) {
        if (this==&arg) { return *this; }
        if (_xobject) { _xobject->reset(); }
        _xobject=arg._xobject;
        arg._xobject=nullptr;
        return *this;
    }

    Item(Item &&arg):_xobject(arg._xobject) {
        arg._xobject=nullptr;
    }

};


}/*_private_QRunOnce_*/

template<typename ... T >
class QRunOnce : public std::tuple< _private_QRunOnce_::Item<T>... > {
    using _Super=std::tuple< _private_QRunOnce_::Item<T>... >;
public:
    QRunOnce(T &...args):_Super(args...) {}
};

template<typename ... T>
inline QRunOnce<T...> makeQRunOnce(T &...args) {
    return QRunOnce<T...>(args...);
}

#endif // QRUNONCE_HPP
