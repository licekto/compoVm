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
my $lcovCommand1 = "lcov --capture --directory ../ -o coverage.info";
my $lcovCommand2 = "lcov --remove coverage.info \"/usr*\" -o coverage.info";
my $lcovCommand3 = "lcov --remove coverage.info \"test/*\" -o coverage.info";
my $lcovCommand4 = "lcov --remove coverage.info \"include/generated/*\" -o coverage.info";
my $lcovCommand5 = "lcov --remove coverage.info \"src/generated/*\" -o coverage.info";
my $genhtmlCommand = "genhtml coverage.info --output-directory ../doc/coverage";

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

say "Running lcov...";
system($lcovCommand1);
system($lcovCommand2);
system($lcovCommand3);
system($lcovCommand4);
system($lcovCommand5);
system($genhtmlCommand);
system("rm ../coverage.info");
say "Code coverage report completed";
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
