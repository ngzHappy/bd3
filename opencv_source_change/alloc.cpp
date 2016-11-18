#include "precomp.hpp"

/*
change modules/core/CMakeLists.txt
set(extra_libs "")
to:
include_directories("D:/x/m/bd3/baidu3/cplusplus_basic")
link_directories("D:/x/m/bd3/baidu3/binlib")
set(extra_libs cplusplus_basic_library)
*/

/*
import memory::malloc
import memory::free
*/
#include <Qt/boost/config.hpp>
namespace memory{
    BOOST_SYMBOL_IMPORT void * malloc(size_t arg);
    BOOST_SYMBOL_IMPORT void free(void * arg);
}

namespace cv
{

/**/
static inline void * ____opencv_Malloc(size_t size){
    return memory::malloc(size);
}
/**/
static inline void ____opencv_Free(void * arg){
    return memory::free(arg);
}

static void* OutOfMemoryError(size_t size)
{
    CV_Error_(CV_StsNoMem, ("Failed to allocate %lu bytes", (unsigned long)size));
    return 0;
}

#if defined WIN32 || defined _WIN32
void deleteThreadAllocData() {}
#endif

void* fastMalloc( size_t size )
{
    uchar* udata = (uchar*)____opencv_Malloc(size + sizeof(void*) + CV_MALLOC_ALIGN);
    if(!udata)
        return OutOfMemoryError(size);
    uchar** adata = alignPtr((uchar**)udata + 1, CV_MALLOC_ALIGN);
    adata[-1] = udata;
    return adata;
}

void fastFree(void* ptr)
{
    if(ptr)
    {
        uchar* udata = ((uchar**)ptr)[-1];
        CV_DbgAssert(udata < (uchar*)ptr &&
               ((uchar*)ptr - udata) <= (ptrdiff_t)(sizeof(void*)+CV_MALLOC_ALIGN));
        ____opencv_Free(udata);
    }
}

}/*namespace cv*/


CV_IMPL void* cvAlloc( size_t size )
{
    return cv::fastMalloc( size );
}

CV_IMPL void cvFree_( void* ptr )
{
    cv::fastFree( ptr );
}

/*end of the file.*/
