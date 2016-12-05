#include "TestMemory.hpp"
#include<mutex>
#include<vector>
#include<memory>
#include<thread>
#include<cstdlib>
#include<cassert>
#include<iostream>

namespace {
class TestClass {
public:
    char data[128];
    void foo() {}
};
}

#include "Reference.hpp"

TestMemory::TestMemory() {

    {
        TestClass v1,v0,v2;
        std::vector< std::reference_wrapper<TestClass>,
            memory::Allocator<std::reference_wrapper<TestClass>>> test;
        test.reserve(128);
        test.push_back(v0);
        test.push_back(v1);
        test.push_back(v2);
        
        std::reference_wrapper<TestClass> rv1(v1);
        
    }

    {
        using namespace utiliy;
        int a=1;
        int b=2;

        std::reference_wrapper<int> ra(a);
        std::reference_wrapper<int> rb(b);

        
    }


    {
        void * data=memory::malloc(4);
        std::cout<<memory::size(data)<<std::endl;
        memory::free(data);
    }

    {
        void * data=memory::malloc(32768);
        std::cout<<memory::size(data)<<std::endl;
        memory::free(data);
    }

    auto test=[]() {

        {
            int *data;
            for (size_t i=sizeof(int); i<1024*33; ++i) {
                for (size_t j=0; j<8; ++j) {
                    data=reinterpret_cast<int *>(memory::malloc(i));
                    *data=332;
                    auto size=memory::size(data);
                    assert(size>0);
                    assert(size>i);
                    assert((size-i)<=100);

                    (void)size;
                    memory::free(data);
                }
            }
        }
    };

    /*test in one thread*/
    test();

    /*test in multi thread*/
    std::thread all_test[]={
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
    };

    for (auto & i:all_test) {
        if (i.joinable()) {
            i.join();
        }
    }

}
