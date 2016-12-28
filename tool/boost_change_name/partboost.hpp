/*headers**************************************************/
#include <boost/bimap.hpp>/*双向map*/
#include <boost/geometry.hpp>/*几何计算库*/
#include <boost/multi_array.hpp>/*多维数组*/
#include <boost/multi_index_container.hpp>/*多索引容器*/
#include <boost/geometry/index/rtree.hpp>/*rtree*/
#include <boost/circular_buffer.hpp>/*循环缓冲区*/
#include <boost/pool/pool.hpp>/*定长内存池*/
#include <boost/pool/pool_alloc.hpp>/*定长内存池*/
#include <boost/pool/singleton_pool.hpp>/*定长内存池*/
#include <boost/icl/interval.hpp>/*区间树*/
#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>
/*headers**************************************************/
/***
***/
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/hashed_index_fwd.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/identity_fwd.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/ordered_index_fwd.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/random_access_index_fwd.hpp>
#include <boost/multi_index/ranked_index.hpp>
#include <boost/multi_index/ranked_index_fwd.hpp>
#include <boost/multi_index/safe_mode_errors.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/sequenced_index_fwd.hpp>
#include <boost/multi_index/tag.hpp>
