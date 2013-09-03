#ifndef _myinit_h_
#define _myinit_h_

// this needs to be included early for MSVC (listing it in Build.PL is not enough)
#include <ostream>

extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "ppport.h"
#undef do_open
#undef do_close
}

// Boost.Geometry
#include <boost/geometry.hpp>

// Slic3r constants
#define EPSILON 1e-4

namespace Slic3r {}
using namespace Slic3r;

#endif
