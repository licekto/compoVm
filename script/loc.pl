#!/usr/bin/perl

use strict;
use warnings;
use feature qw(say);

my $command = "cloc .. --exclude-dir=lib,nbproject,doc,build,bin,generated";

system($command);

