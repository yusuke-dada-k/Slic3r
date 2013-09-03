#ifndef slic3r_Polygon_hpp_
#define slic3r_Polygon_hpp_

#include <myinit.h>
#include <vector>
#include "Line.hpp"
#include "MultiPoint.hpp"
#include "Polyline.hpp"

namespace Slic3r {

class Polygon : public MultiPoint {
    public:
    Point* last_point() const;
    SV* to_SV_ref();
    SV* to_SV_clone_ref() const;
    Lines lines() const;
    Polyline* split_at(const Point* point);
    Polyline* split_at_index(int index);
    Polyline* split_at_first_point();
    double area() const;
    bool is_counter_clockwise() const;
    bool is_clockwise() const;
    bool make_counter_clockwise();
    bool make_clockwise();
    bool is_valid() const;
    bool encloses_point(Point* point) const;
};

typedef std::vector<Polygon> Polygons;

}

// Boost.Geometry
#include <boost/geometry/geometries/register/ring.hpp>
BOOST_GEOMETRY_REGISTER_RING(Polygon);

#include <boost/range.hpp>
namespace boost
{
    template<>
    struct range_iterator<Polygon>
    { typedef Points::iterator type; };

    template<>
    struct range_const_iterator<Polygon>
    { typedef Points::const_iterator type; };
}

namespace Slic3r {
    inline Points::iterator
    range_begin(Polygon& poly) {return poly.points.begin();}
    
    inline Points::iterator
    range_end(Polygon& poly) {return poly.points.end();}
    
    inline Points::const_iterator
    range_begin(const Polygon& poly) {return poly.points.begin();}
    
    inline Points::const_iterator
    range_end(const Polygon& poly) {return poly.points.end();}
}
// end Boost.Geometry

#endif
