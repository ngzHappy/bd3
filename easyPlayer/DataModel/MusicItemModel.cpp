#include "MusicItem.hpp"
#include "MusicItemModel.hpp"
#include "private/_.p._MusicItemModel.hpp"

MusicItemModel::MusicItemModel(_PrivateMusicItemModel*p,QObject*s):Super(s){
    $m$thisp=p;
}

MusicItemModel::~MusicItemModel(){
    delete $m$thisp;
}

MusicItemModel::MusicItemModel(QObject * parent)
    :MusicItemModel(new _PrivateMusicItemModel,parent){}

_PrivateMusicItemModel::~_PrivateMusicItemModel(){
}



