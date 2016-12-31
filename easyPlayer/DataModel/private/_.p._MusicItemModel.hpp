#ifndef _p_MUSIC_ITEM__HPP_0x22896_MODEL_
#define _p_MUSIC_ITEM__HPP_0x22896_MODEL_

#include <cplusplus_basic.hpp>
#include "../MusicItem.hpp"

/*
 * 因为只是测试，所以用Boost.Multiindex代替数据库
 * 将boost替换为Qt/boost 防止与系统自带boost冲突
*/
#include <Qt/boost/multi_index/tag.hpp>
#include <Qt/boost/multi_index/member.hpp>
#include <Qt/boost/multi_index/mem_fun.hpp>
#include <Qt/boost/multi_index/identity.hpp>
#include <Qt/boost/multi_index/indexed_by.hpp>
#include <Qt/boost/multi_index/global_fun.hpp>
#include <Qt/boost/multi_index/ranked_index.hpp>
#include <Qt/boost/multi_index/hashed_index.hpp>
#include <Qt/boost/multi_index/ordered_index.hpp>
#include <Qt/boost/multi_index/composite_key.hpp>
#include <Qt/boost/multi_index/key_extractors.hpp>
#include <Qt/boost/multi_index/sequenced_index.hpp>
#include <Qt/boost/multi_index/safe_mode_errors.hpp>
#include <Qt/boost/multi_index/random_access_index.hpp>
#include <Qt/boost/multi_index_container.hpp>/*包含Boost.Multiindex*/

#include <QtCore/qstring.h>

class _PrivateMusicItemModel{
    template<typename TA,typename TB>
    using multi_index_container=boost::multi_index::multi_index_container<TA,TB,memory::Allocator<TA>>;
public:
    virtual ~_PrivateMusicItemModel();

    class GroupedItem{
        using _T_=std::shared_ptr<MusicItem>;
        static MusicItem* _p_get(const _T_&arg){return arg.get();}
    public:

        using data_type_container = multi_index_container<_T_,
            boost::multi_index::indexed_by<
            boost::multi_index::random_access<>,/*类似std.vector*/
            boost::multi_index::ordered_unique<
            boost::multi_index::global_fun<const _T_&,MusicItem*,&GroupedItem::_p_get>>/*类似std.map*/
            >>;

        class OtherData {
        public:
            data_type_container $m$container;
            OtherData() { $m$container.reserve(128)/*每个分组预设128个元素*/; }
        private:
            CPLUSPLUS_OBJECT(OtherData)
        };

        const QString & getGroupName()const{ return *$m$groupName; }
        void setGroupName(std::shared_ptr<QString>arg) { $m$groupName=std::move(arg); }
        void setGroupName(QString arg) {*$m$groupName=std::move(arg);}

        data_type_container & getDataContainer() const { return ($m$data->$m$container); }

        GroupedItem():
            $m$groupName(memory::make_shared<QString>() ),
            $m$data(memory::make_shared<OtherData>()){}

        GroupedItem(std::shared_ptr<QString>arg):
            $m$groupName(std::move(arg)),
            $m$data(memory::make_shared<OtherData>()){}

        GroupedItem(QString arg):GroupedItem() {
            *$m$groupName=std::move(arg);
        }

        GroupedItem(const GroupedItem&)=default;
        GroupedItem(GroupedItem&&)=default;
        GroupedItem&operator=(const GroupedItem&)=default;
        GroupedItem&operator=(GroupedItem&&)=default;

        std::shared_ptr<QString> $m$groupName;
        std::shared_ptr<OtherData> $m$data;

    private:
         CPLUSPLUS_OBJECT(GroupedItem)
    };

    using data_type_container = multi_index_container<GroupedItem,
    boost::multi_index::indexed_by<
    boost::multi_index::random_access<>,/*类似std.vector*/
    boost::multi_index::ordered_unique<
    boost::multi_index::const_mem_fun<GroupedItem,const QString &,&GroupedItem::getGroupName>>/*类似std.map*/
    >>;

    data_type_container $m$data;

    _PrivateMusicItemModel() {
        $m$data.reserve(64)/*预计有64个分组*/;
    }

private:
    CPLUSPLUS_OBJECT(_PrivateMusicItemModel)
};

#endif




