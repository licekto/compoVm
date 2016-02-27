#!/usr/bin/perl

use strict;
use warnings;
use feature qw(say);
use Cwd qw(abs_path);
use File::Copy;
use File::Path qw(make_path remove_tree);

# This command uses google-style formatting, tab indentation,
# indents namespaces and classes and does not preserve original files (--suffix=none).
# It also runs recursively for required pattern.
my $astyleCommand = "astyle --style=google --indent=tab --indent-namespaces --indent-classes --suffix=none --recursive \"##PATTERN##\"";

my $headersPattern = "*.h";
my $headersDirectory = "../include";
my $sourcesPattern = "*.cpp";
my $sourcesDirectory = "../src";


say "Running astyle formatter...";

chdir($headersDirectory);
my $command = $astyleCommand;
$command =~ s/##PATTERN##/$headersPattern/g;
system($command);

chdir($sourcesDirectory);
my $command = $astyleCommand;
$command =~ s/##PATTERN##/$sourcesPattern/g;
system($command);

say "Formatting done";
