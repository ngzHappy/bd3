#include "_PrivateBaiduStaticData.hpp"

namespace baidu{

_PrivateBaiduStaticData::_PrivateBaiduStaticData(){
}

namespace{
static memory::StaticData<_PrivateBaiduStaticData> static_data__PrivateBaiduStaticData;
}

_PrivateBaiduStaticData *getBaiduStaticData(){
    static memory::StaticPointer<_PrivateBaiduStaticData> ans{&static_data__PrivateBaiduStaticData};
    return ans.pointer();
}

}/*baidu*/
