#!/usr/bin/perl

use strict;
use warnings;

use Slic3r::XS;
use Test::More tests => 1;

ok 'okay';

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

if (0) {
    my $points = [ map Slic3r::Point->new(@$_), @$square ];
    my $hull = Slic3r::Geometry::convex_hull($points);
    ok $hull->is_counter_clockwise, 'convex_hull is ccw';
    ok !$hull->[-1]->coincides_with($hull->first_point), 'hull polygon is open';
    use XXX; XXX $hull->pp;
    is_deeply $hull->pp, [ [5,2], [20,10], [200,100], [50,20], [5,2] ], 'convex_hull';
}

if (0) {
    my $expolygon = Slic3r::ExPolygon->new($square, $hole_in_square);
    my $polyline = Slic3r::Polyline->new([0,150], [300,150]);
    my $result = Slic3r::Geometry::expolygons_polylines_intersection([$expolygon], [$polyline]);
    use XXX; XXX (map $_->pp, @$result);
    # fails because Boost isn't honoring winding order and closure yet
}

__END__
