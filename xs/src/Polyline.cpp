#include "Polyline.hpp"

namespace Slic3r {

Point*
Polyline::last_point() const
{
    return new Point(this->points.back());
}

void
Polyline::lines(Lines &lines) const
{
    lines.clear();
    for (int i = 0; i < this->points.size()-1; i++) {
        lines.push_back(Line(this->points[i], this->points[i+1]));
    }
}

SV*
Polyline::to_SV_ref()
{
    SV* sv = newSV(0);
    sv_setref_pv( sv, "Slic3r::Polyline::Ref", (void*)this );
    return sv;
}

SV*
Polyline::to_SV_clone_ref() const
{
    SV* sv = newSV(0);
    sv_setref_pv( sv, "Slic3r::Polyline", new Polyline(*this) );
    return sv;
}

double
Polyline::length() const
{
    return boost::geometry::length(*this);
}

// removes the given distance from the end of the polyline
void
Polyline::clip_end(double d)
{
    while (d > 0) {
        Point last_point = this->points.back();
        this->points.pop_back();
        if (this->points.size() == 0) break;
        
        Line last_segment = Line(last_point, this->points.back());
        double last_segment_length = last_segment.length();
        if (last_segment_length <= d) {
            d -= last_segment_length;
            continue;
        }
        
        Point* p = last_segment.point_at(d);
        this->points.push_back(*p);
        delete p;
        break;
    }
}

}
