#include <cstring>
#include <fstream>
#include <iostream>

#include "parser/parserWrapper.h"
#include "exceptions/runtime/wrongParametersException.h"
#include "definitions/interpreterDefinitions.h"

std::string readFile(const std::string& filename) {
    	std::ifstream infile(filename);
        if (!infile.good()) {
            throw exceptions::runtime::CWrongParametersException("File '" + filename + "' does not exist!");
        }

        std::string line, code;
        
        while (std::getline(infile, line)) {
            code += line;
        }
        
	infile.close();
        
        return code;
}

ptr(core_interpreter) init() {
        ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());
        ptr(interpreter::memory::memspace::CDescriptorTable) table = new_ptr(interpreter::memory::memspace::CDescriptorTable)();
        ptr(interpreter::memory::memspace::CMemory) memory = new_ptr(interpreter::memory::memspace::CMemory)();
        ptr(core_bootstrap1) bootstrap1 = new_ptr(core_bootstrap1)(new_ptr(interpreter::core::CCoreModules)(parser), nullptr, memory);
        memory->setBootstrap1(bootstrap1);
        ptr(core_bootstrap2) bootstrap2 = new_ptr(core_bootstrap2)(bootstrap1);
        ptr(core_interpreter) interpreter = new_ptr(core_interpreter)(parser, bootstrap2, table);
        bootstrap1->setInterpreter(interpreter);
        
        return interpreter;
}

int main(int argc, char **argv) {

	if (argc != 2) {
		std::cerr << "Wrong args" << std::endl;
		return -1;
	}

	std::string code = readFile(std::string(argv[1]));
        
        ptr(core_interpreter) interpreter = init();
        
        interpreter->run(code);

	return 0;
}