#include "BoostTest.hpp"

#include <Qt/boost/multi_index_container.hpp>
#include <Qt/boost/multi_index/member.hpp>
#include <Qt/boost/multi_index/ordered_index.hpp>
#include <Qt/boost/multi_index/sequenced_index.hpp>
#include <Qt/boost/multi_index/random_access_index.hpp>

class Test{
public:
};

BoostTest::BoostTest(){

    using x = boost::multi_index_container<
            Test,
            boost::multi_index::indexed_by<
            boost::multi_index::random_access<>
            >>;

}



