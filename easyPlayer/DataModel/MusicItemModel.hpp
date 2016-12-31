#ifndef __MUSIC_ITEM__HPP_0x22896_MODEL_
#define __MUSIC_ITEM__HPP_0x22896_MODEL_

#include <cplusplus_basic.hpp>
#include <QtCore/qabstractitemmodel.h>
#include "MusicItem.hpp"

#ifndef $m$MUSICITEMMODEL_PROTECTED
#define $m$MUSICITEMMODEL_PROTECTED protected
#endif

class _PrivateMusicItemModel;
class MusicItemModel :public QAbstractItemModel {
    Q_OBJECT
private:
    using Super=QAbstractItemModel;
protected:
    MusicItemModel(_PrivateMusicItemModel*,QObject*);
public:
    MusicItemModel(QObject * parent=nullptr);
    virtual ~MusicItemModel();
$m$MUSICITEMMODEL_PROTECTED:
    _PrivateMusicItemModel*$m$thisp=nullptr;
private:
    CPLUSPLUS_OBJECT(MusicItemModel)
};

#endif




