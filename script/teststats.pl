#!/usr/bin/perl

use strict;
use warnings;
use feature qw(say);
use Cwd qw(abs_path);
use File::Copy;
use File::Path qw(make_path remove_tree);

my $testCommand = "ctest -T Test -D ExperimentalBuild -D ExperimentalTest -D ExperimentalMemCheck";
my $oclintCommand = "oclint-json-compilation-database -e ../src/generated/parser.cpp -e ../src/generated/lexer.cpp -- -report-type html -o oclint.html";

chdir("../build/");
system($testCommand);

my $oclintFile = "compile_commands.json";
copy($oclintFile, "../" . $oclintFile);
chdir("..");
system($oclintCommand);

unlink($oclintFile);

if (not -d "doc/stats")
{
	make_path("doc/stats");
}
move("build/valgrind.xml", "doc/stats");
move("oclint.html", "doc/stats");
move("script/Testing", "build/");

my $testingDir = "build/Testing/";
opendir(my $dh, $testingDir);

my $testingDirPattern = "[0-9]{8}-[0-9]{4}";

my @files = grep(/$testingDirPattern/, readdir($dh));

closedir($dh);

my $testingXml = $testingDir . $files[0] . "/Test.xml";
move($testingXml, "doc/stats");

