#ifndef slic3r_Polyline_hpp_
#define slic3r_Polyline_hpp_

#include "Line.hpp"
#include "MultiPoint.hpp"

namespace Slic3r {

class Polyline : public MultiPoint {
    public:
    Point* last_point() const;
    void lines(Lines &lines) const;
    SV* to_SV_ref();
    SV* to_SV_clone_ref() const;
    double length() const;
};

typedef std::vector<Polyline> Polylines;

}

// Boost.Geometry
#include <boost/geometry/geometries/register/linestring.hpp>
BOOST_GEOMETRY_REGISTER_LINESTRING(Polyline)

#include <boost/range.hpp>
namespace boost
{
    template<>
    struct range_iterator<Polyline>
    { typedef Points::iterator type; };

    template<>
    struct range_const_iterator<Polyline>
    { typedef Points::const_iterator type; };
}

namespace Slic3r {
    inline Points::iterator
    range_begin(Polyline& poly) {return poly.points.begin();}
    
    inline Points::iterator
    range_end(Polyline& poly) {return poly.points.end();}
    
    inline Points::const_iterator
    range_begin(const Polyline& poly) {return poly.points.begin();}
    
    inline Points::const_iterator
    range_end(const Polyline& poly) {return poly.points.end();}
}
// end B
// end Boost.Geometry

#endif
