#ifndef __OPEN_CV_UTILITY_0x998127_HPP
#define __OPEN_CV_UTILITY_0x998127_HPP

#include "ImageShowUtility.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

namespace __private {
namespace __ImageShowUtility {

using cvfloat_type=cv::Point2f::value_type;
using point2fvector=std::vector<cv::Point2f,memory::Allocator<cv::Point2f>>;

template<typename _TB,typename _TE>
point2fvector toCVFloat32Point2Vector(const _TB & argb,const _TE & arge) {
    auto size_=Distance<const _TB &,const _TE &>::value(argb,arge);
    point2fvector ans;
    ans.reserve(size_);
    for (auto i=argb; i!=arge; ++i) {
        ans.emplace_back(
            static_cast<cvfloat_type>(autoGetX(*i)),
            static_cast<cvfloat_type>(autoGetY(*i))
        );
    }
    return std::move(ans);
}

template<typename _TB>
point2fvector toCVFloat32Point2Vector(const _TB & argb,size_t size_) {
    point2fvector ans;
    ans.reserve(size_);
    size_t count_=0;
    for (auto i=argb; count_<size_; ++i,++count_) {
        ans.emplace_back(
            static_cast<cvfloat_type>(autoGetX(*i)),
            static_cast<cvfloat_type>(autoGetY(*i))
        );
    }
    return std::move(ans);
}

}/*__ImageShowUtility*/
}/*__private*/

using __private::__ImageShowUtility::toCVFloat32Point2Vector;

#endif
