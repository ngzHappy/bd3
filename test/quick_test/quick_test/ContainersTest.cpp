#include "ContainersTest.hpp"
#include <containers/containers.hpp>

ContainersTest::ContainersTest(){
    {
        containers::array<int,12> test;
        test[0]=1;
    }

    {
        containers::map<int,double> test;
        test.find(12);
    }

}






