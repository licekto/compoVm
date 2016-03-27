#include <cstring>
#include <fstream>
#include <iostream>

#include "parser/parserWrapper.h"

int main(int argc, char **argv) {

	if (argc != 2) {
		std::cerr << "Wrong args" << std::endl;
		return -1;
	}

	std::string filename = std::string(argv[1]);

	std::ifstream infile;
	infile.open(filename);

	infile.close();

	// TĚPÉRO

	return 0;
}