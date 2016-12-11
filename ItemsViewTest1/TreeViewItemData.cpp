#include "TreeViewItemData.hpp"

TreeViewItemData::TreeViewItemData(){

}

std::shared_ptr<TreeViewItemData> TreeViewItemData::instance(){
    std::shared_ptr<TreeViewItemData> varAns { new TreeViewItemData };
    varAns->$m$Watcher=varAns;
    return std::move(varAns);
}
