#include <cassert>
#include "thread_shadow_thread.hpp"

namespace thread {

ShadowThread::~ShadowThread(){

}

namespace  ____ShadowThread{
/*this will not be deleted*/
static memory::StaticData<ShadowThread> _data;
}/*____ShadowThread*/

ShadowThread * ShadowThread::instance(){
   static memory::StaticPoionter<ShadowThread> ans(
               ____ShadowThread::_data);
   return ans.pointer();
}

ShadowThread::ShadowThread(){

}

}/*thread*/






