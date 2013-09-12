#!/usr/bin/perl

use strict;
use warnings;

use Slic3r::XS;
use Test::More tests => 1;

ok 'okay';

if (0) {
    my $points = [ map { Slic3r::Point->new(20*$_, 10*$_), Slic3r::Point->new(5*$_, 2*$_) } (1..10) ];
    my $hull = Slic3r::Geometry::convex_hull($points);
    ok $hull->is_counter_clockwise, 'convex_hull is ccw';
    use XXX; XXX $hull->pp;
    is_deeply $hull->pp, [ [5,2], [20,10], [200,100], [50,20], [5,2] ], 'convex_hull';
}

my $square = [  # ccw
    [100, 100],
    [200, 100],
    [200, 200],
    [100, 200],
];
my $hole_in_square = [  # cw
    [140, 140],
    [140, 160],
    [160, 160],
    [160, 140],
];
my $expolygon = Slic3r::ExPolygon->new($square, $hole_in_square);
my $polyline = Slic3r::Polyline->new([0,150], [300,150]);

if (0) {
    my $polylines = Slic3r::Geometry::expolygons_polylines_intersection([$expolygon], [$polyline]);
    use XXX; XXX map $_->pp, @$polylines;
    # fails because Boost isn't honoring winding order and closure yet
}

__END__
