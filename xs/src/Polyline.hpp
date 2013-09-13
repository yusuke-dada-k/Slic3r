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
    void clip_end(double d);
    
    #ifndef NOBOOST
    std::size_t size() const;
    void clear();
    const Point& operator[] (const int nIndex) const;
    #endif
};

typedef std::vector<Polyline> Polylines;

}

#ifndef NOBOOST
#include <boost/geometry/geometries/register/linestring.hpp>
#include <boost/geometry/multi/geometries/register/multi_linestring.hpp>
BOOST_GEOMETRY_REGISTER_LINESTRING(Polyline)
BOOST_GEOMETRY_REGISTER_MULTI_LINESTRING(Polylines);

namespace boost { namespace geometry { namespace traits {
    template<>
    struct clear<Polyline>
    {
        static inline void apply(Polyline& polyline)
        {
            polyline.points.clear();
        }
    };
    
    template<>
    struct resize<Polyline>
    {
        static inline void apply(Polyline& polyline, std::size_t new_size)
        {
            polyline.points.resize(new_size);
        }
    };
    
    template<>
    struct push_back<Polyline>
    {
        static inline void apply(Polyline& polyline, Point const& point)
        {
            polyline.points.push_back(point);
        }
    };
}}}

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
#endif

#endif
