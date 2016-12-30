#ifndef _Private_ONEDEEPTREEVIEW_HPP
#define _Private_ONEDEEPTREEVIEW_HPP

#include <set>
#include <vector>

#include "../OneDeepTreeView.hpp"
#include "../OneDeepTreeDelegate.hpp"
#include "../OneDeepTreeItemWidget.hpp"

class _PrivateOneDeepTreeView{
public:
    ~_PrivateOneDeepTreeView();
    std::uintmax_t $m$gc_tag=0;

    template<typename $m$T>
    using vector=std::vector<$m$T,memory::Allocator<$m$T>>;
    template<typename $m$T,typename $m$C>
    using set=std::set<$m$T,$m$C,memory::Allocator<$m$T>>;

    class TreeViewItemWidgetCompare {
        using T=const OneDeepTreeItemWidget *;
        using U=const QModelIndex &;
    public:
        using is_transparent = std::less<void>::is_transparent;
        bool operator()(T l,T r)const {
            return l->getModelIndex()<r->getModelIndex();
        }
        bool operator()(U l,U r)const { return l<r; }
        bool operator()(U l,T r)const { return l<r->getModelIndex(); }
        bool operator()(T l,U r)const { return l->getModelIndex()<r; }
    };

    set<OneDeepTreeItemWidget *,TreeViewItemWidgetCompare> $m$OpendWidgets;

private:
    CPLUSPLUS_OBJECT(_PrivateOneDeepTreeView)
};

#endif // ONEDEEPTREEVIEW_HPP










