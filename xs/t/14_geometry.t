#!/usr/bin/perl

use strict;
use warnings;

use Slic3r::XS;
use Test::More tests => 1;

{
    my $points = [ map { Slic3r::Point->new(20*$_, 10*$_), Slic3r::Point->new(5*$_, 2*$_) } (1..10) ];
    my $hull = Slic3r::Geometry::convex_hull($points);
    is_deeply $hull->pp, [ [5,2], [20,10], [200,100], [50,20], [5,2] ], 'convex_hull';
}

__END__
