
#ifndef _SPIN_BOX_HPP__0x0098
#define _SPIN_BOX_HPP__0x0098

//#include <iostream>
//static int test = 0;

namespace{
namespace _pm_file {

class spin_mutex {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    spin_mutex() = default;
    spin_mutex(const spin_mutex&) = delete;
    spin_mutex& operator= (const spin_mutex&) = delete;
    void lock() {
        while(flag.test_and_set()){ 
            //std::cout<<"."<<++test; 
        }
    }
    void unlock() {
        flag.clear();
    }
};

}/*_pm_file*/
}/*namespace*/


#endif
