#ifndef slic3r_ExPolygon_hpp_
#define slic3r_ExPolygon_hpp_

#include "Polygon.hpp"
#include <vector>

namespace Slic3r {

class ExPolygon
{
    public:
    Polygon contour;
    Polygons holes;
    void from_SV(SV* poly_sv);
    void from_SV_check(SV* poly_sv);
    SV* to_AV();
    SV* to_SV_ref();
    SV* to_SV_clone_ref() const;
    SV* to_SV_pureperl() const;
    void scale(double factor);
    void translate(double x, double y);
    void rotate(double angle, Point* center);
    double area() const;
    bool is_valid() const;
    bool encloses_point(Point* point) const;
};

typedef std::vector<ExPolygon> ExPolygons;

}

#ifndef NOBOOST
namespace boost {
    namespace geometry {
        namespace traits {
            template<> struct tag<ExPolygon> { typedef polygon_tag type; };
            template<> struct ring_const_type<ExPolygon> { typedef const Polygon& type; };
            template<> struct ring_mutable_type<ExPolygon> { typedef Polygon& type; };
            template<> struct interior_const_type<ExPolygon> { typedef const Polygons type; };
            template<> struct interior_mutable_type<ExPolygon> { typedef Polygons type; };

            template<> struct exterior_ring<ExPolygon>
            {
                static Polygon& get(ExPolygon& p)
                {
                    return p.contour;
                }
                static Polygon const& get(ExPolygon const& p)
                {
                    return p.contour;
                }
            };

            template<> struct interior_rings<ExPolygon>
            {
                static Polygons get(ExPolygon& p)
                {
                    return p.holes;
                }
                static const Polygons get(ExPolygon const& p)
                {
                    return p.holes;
                }
            };
        }
    }
} // namespace boost::geometry::traits

#include <boost/geometry/multi/geometries/register/multi_polygon.hpp>
BOOST_GEOMETRY_REGISTER_MULTI_POLYGON(ExPolygons);
#endif

#endif
