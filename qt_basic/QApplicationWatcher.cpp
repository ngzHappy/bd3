#include <mutex>
#include "QApplicationWatcher.hpp"

namespace qappwatcher{

namespace {
using mutex_data_t=std::aligned_storage_t<sizeof(std::mutex),alignof(std::mutex)>;
mutex_data_t mutex_data;
}/*namespace*/

std::mutex * getMutex(){
    static auto ans = ::new(&mutex_data) std::mutex;
    return ans;
}

}

