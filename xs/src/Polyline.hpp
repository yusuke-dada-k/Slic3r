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

#include <boost/geometry/geometries/register/linestring.hpp>
BOOST_GEOMETRY_REGISTER_LINESTRING(Points)

#endif
