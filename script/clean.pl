#!/usr/bin/perl

use strict;
use warnings;
use feature qw(say);
use File::Path qw(rmtree);

rmtree("../bin");
rmtree("../build");
rmtree("../doc");
rmtree("../include/generated");
rmtree("../src/generated");

