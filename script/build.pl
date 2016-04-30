#!/usr/bin/perl

use strict;
use warnings;
use feature qw(say);
use Cwd qw(abs_path);
use File::Copy;
use File::Path qw(make_path remove_tree);

sub usage() {
	say "Usage: build.pl --makefile=<makefile_type>";
	say "	<makefile_type>: ninja - Ninja parallel build system";
	say "	<makefile_type>: unix - Standard unix makefile";
	exit;
}

my $makefileType;

if ($#ARGV == 0) {
       	if ($ARGV[0] eq "--makefile=ninja") {
		$makefileType = "Ninja";
	}
       	elsif ($ARGV[0] eq "--makefile=unix") {
		$makefileType = "Unix Makefiles";
	}
	else {
		usage();
	}
}
else {
	usage();
}

my $cmakeCommand = "cmake -DBuildRelease=ON -G \"$makefileType\" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ -DCMAKE_C_FLAGS_DEBUG=\"-g3 -gdwarf-2\" -DCMAKE_CXX_FLAGS_DEBUG=\"-g3 -gdwarf-2\" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..";

if (not -d "../build") {
	system("mkdir ../build");
}

chdir ("../build");

system $cmakeCommand;

if ($makefileType eq "Ninja") {
	system "ninja";
}
elsif ($makefileType eq "Unix Makefiles") {
	system "make";
}

