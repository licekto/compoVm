#include <cstring>
#include <fstream>

#include "parserWrapper.h"

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Wrong args" << std::endl;
        return -1;
    }

    std::string filename = std::string(argv[1]);

    std::ifstream infile;
    infile.open(filename);

    Lexer lexer;
    ParserWrapper parser(&lexer);

    while (1) {
        if (!parser.parse(infile)) {
            break;
        }
    }

    infile.close();
    
    std::cout << *parser.getRoot() << std::endl;

    return 0;
}