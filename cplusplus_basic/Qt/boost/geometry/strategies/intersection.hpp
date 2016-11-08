﻿// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP

#include <Qt/boost/geometry/core/point_type.hpp>
#include <Qt/boost/geometry/geometries/segment.hpp>

#include <Qt/boost/geometry/policies/relate/intersection_points.hpp>
#include <Qt/boost/geometry/policies/relate/direction.hpp>
#include <Qt/boost/geometry/policies/relate/tupled.hpp>

#include <Qt/boost/geometry/strategies/side.hpp>
#include <Qt/boost/geometry/strategies/intersection_result.hpp>

#include <Qt/boost/geometry/strategies/cartesian/cart_intersect.hpp>
#include <Qt/boost/geometry/policies/robustness/segment_ratio_type.hpp>


namespace boost { namespace geometry
{


/*!
\brief "compound strategy", containing a segment-intersection-strategy
       and a side-strategy
 */
template
<
    typename Tag,
    typename Geometry1,
    typename Geometry2,
    typename IntersectionPoint,
    typename RobustPolicy,
    typename CalculationType = void
>
struct strategy_intersection
{
private :
    // for development BOOST_STATIC_ASSERT((! boost::is_same<RobustPolicy, void>::type::value));

    typedef typename geometry::point_type<Geometry1>::type point1_type;
    typedef typename geometry::point_type<Geometry2>::type point2_type;
    typedef typename model::referring_segment<point1_type const> segment1_type;
    typedef typename model::referring_segment<point2_type const> segment2_type;

    typedef segment_intersection_points
    <
        IntersectionPoint,
        typename geometry::segment_ratio_type
        <
            IntersectionPoint, RobustPolicy
        >::type
    > ip_type;

public:
    typedef strategy::intersection::relate_cartesian_segments
            <
                policies::relate::segments_tupled
                    <
                        policies::relate::segments_intersection_points
                            <
                                ip_type
                            > ,
                        policies::relate::segments_direction
                    >,
                CalculationType
            > segment_intersection_strategy_type;

    typedef typename strategy::side::services::default_strategy
        <
            Tag,
            CalculationType
        >::type side_strategy_type;

    typedef RobustPolicy rescale_policy_type;
};

// Version for box_box intersection or other detail calls not needing a strategy
struct strategy_intersection_empty {};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP
