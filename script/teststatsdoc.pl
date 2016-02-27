#!/usr/bin/perl

use strict;
use warnings;
use feature qw(say);
use Cwd qw(abs_path);
use File::Copy;
use File::Path qw(make_path remove_tree);

my $testCommand = "ctest -T Test -D ExperimentalBuild -D ExperimentalTest -D ExperimentalMemCheck";
my $oclintCommand = "oclint-json-compilation-database -e ../src/generated/parser.cpp -e ../src/generated/lexer.cpp -- -rc=LONG_LINE=200 -report-type html -o oclint.html";
my $doxygenCommand = "doxygen Doxyfile";
my $cppcheckCommand = "cppcheck -j 4 -i src/generated/ -i include/generated/ src/ include/ --force --enable=warning,performance,information,style --xml 2> cppcheck.xml";

chdir("../resources");
say "Running Doxygen...";
system($doxygenCommand);
say "Doxygen completed";
say "-----------------------------------\n";

chdir("../build/");
say "Running tests...";
system($testCommand);
say "Tests completed";
say "-----------------------------------\n";

my $oclintFile = "compile_commands.json";
copy($oclintFile, "../" . $oclintFile);
chdir("..");
say "Running OCLint...";
system($oclintCommand);
say "OCLint completed";
say "-----------------------------------\n";
say "Running CPPCheck...";
system($cppcheckCommand);
say "CPPCheck completed";
say "-----------------------------------\n";


say "Cleaning directories...";
unlink($oclintFile);

if (not -d "doc/stats")
{
	make_path("doc/stats");
}
move("build/valgrind.xml", "doc/stats");
move("oclint.html", "doc/stats");
move("cppcheck.xml", "doc/stats");
move("script/Testing", "build/");

my $testingDir = "build/Testing/";
opendir(my $dh, $testingDir);

my $testingDirPattern = "[0-9]{8}-[0-9]{4}";

my @files = grep(/$testingDirPattern/, readdir($dh));

closedir($dh);

my $testingXml = $testingDir . $files[0] . "/Test.xml";
move($testingXml, "doc/stats/tests.xml");

say "Cleaning completed";
