#ifndef TREEVIEWITEMDATALIST_HPP
#define TREEVIEWITEMDATALIST_HPP

#include <vector>
#include <QtCore/qstring.h>
#include "cplusplus_basic.hpp"
#include "TreeViewItemData.hpp"

class TreeViewItemDataList{
    template<typename $m$T> using vector=std::vector<$m$T>;
    std::vector< std::shared_ptr< TreeViewItemData > > $m$Data;
    QString $m$Title;
public:
    TreeViewItemDataList();
    int size() const{ return static_cast<int>($m$Data.size()); }
    std::shared_ptr< TreeViewItemData > getData(int n)const{ return  $m$Data[n]; }
    void addData(std::shared_ptr< TreeViewItemData > && arg){ $m$Data.push_back(std::move(arg)); }
    void addData(const std::shared_ptr< TreeViewItemData > & arg){$m$Data.push_back(arg);}

    auto getTitle() const { return $m$Title; }
    void setTitle(const QString & arg){ $m$Title=arg; }
    void setTitle(QString && arg){ $m$Title=std::move(arg); }
private:
    CPLUSPLUS_OBJECT(TreeViewItemDataList)
};

#endif // TREEVIEWITEMDATALIST_HPP
