#!/usr/bin/perl

use strict;
use warnings;

my $range = 100;
my $coor;

# generates 100 random 5-dimensional 
# points with coordinates from 0 to 100 
for my $i (0..100) {
    for my $j (0..4) {
	$coor = rand($range);
	printf "%.3f ", $coor;
    }
    if ($i < 100) {
        print "\n";
    }
}
