#ifndef TREEVIEWITEMDATA_HPP
#define TREEVIEWITEMDATA_HPP

#include <QtCore/qobject.h>
#include <cplusplus_basic.hpp>

class TreeViewItemData final {
protected:
    TreeViewItemData();
    std::weak_ptr<TreeViewItemData> $m$Watcher;
public:
    using type = std::shared_ptr<TreeViewItemData>;
    static type instance();
    auto getWatcher() const {return $m$Watcher;}
private:
    CPLUSPLUS_OBJECT(TreeViewItemData)
};

Q_DECLARE_METATYPE(std::shared_ptr<TreeViewItemData>)

#endif // TREEVIEWITEMDATA_HPP



