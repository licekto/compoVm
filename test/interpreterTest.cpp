#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "logger/logger.h"

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"
#include "parser/lexer.h"
#include "parser/parserWrapper.h"
#include "ast/visitor/semanticCheckVisitor.h"
#include "ast/semantic/syntaxDescriptorsTable.h"
#include "exceptions/semantic/emptyProgramException.h"
#include "exceptions/semantic/undefinedDescriptorException.h"
#include "exceptions/semantic/undefinedInterfaceException.h"
#include "exceptions/semantic/redefinedDescriptorException.h"
#include "exceptions/semantic/redefinedInterfaceException.h"
#include "exceptions/semantic/wrongBaseTypeException.h"
#include "exceptions/semantic/bidirectionalPortNotSupportedException.h"
#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/core/bootstrap.h"

BOOST_AUTO_TEST_SUITE(interpreterTest)


// Global parser for testing purposes
ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());
ptr(interpreter::core::CCoreModules) coreModules = new_ptr(interpreter::core::CCoreModules)();
ptr(interpreter::core::CBootstrap) bootstrap = new_ptr(interpreter::core::CBootstrap)(new_ptr(interpreter::core::CCoreModules)(parser));
ptr(interpreter::memory::memspace::CDescriptorTable) table = new_ptr(interpreter::memory::memspace::CDescriptorTable)();
ptr(interpreter::core::CInterpreter) interpreter = new_ptr(interpreter::core::CInterpreter)(parser, bootstrap, table);

BOOST_AUTO_TEST_CASE(basicTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Test {\
    }\
    descriptor CompoContainer {\
        service main() {\
            c := Test.new();\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    //interpreter->run(program);
    
    // Clear AST for next test
    parser->clearAll();
}

BOOST_AUTO_TEST_CASE(calcTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Calc {\
        provides {\
                arithmetic : { add(x,y); mul(x,y); pow(base,exp) };\
                probability : { rand() };\
        }\
        requires {\
                randGen : { getRandVal(seed) };\
        }\
        service add(x, y) { return x+y; }\
        service mul(x, y) { return x*y; }\
        service pow(base, exp) {\
                | res i |\
                res := 1;\
                for (i := 0; i < exp; i := i + 1) {\
                        res := self.mul(res, base);\
                }\
                return res;\
        }\
        service rand() {\
                return randGen.getRandVal(101);\
        }\
    }\
\
    descriptor RandomGen {\
        provides {\
            default : { getRandVal(seed) };\
        }\
        service getRandVal(seed) {\
            return 15;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            c := Calc.new();\
            connect randGen@c to default@(RandomGen.new());\
            c.add(c.rand(),1);\
            c.mul(3,c.pow(2,3));\
        }\
    }");
    
    // Parse input and create AST
    //parser->parseAll(input);
    
    //ptr(ast_program) program = parser->getRootNode();
    
    
    //ptr(ast::visitors::CSemanticCheckVisitor) visitor = new_ptr(ast::visitors::CSemanticCheckVisitor)(parser->getDescriptorTable());

    //program->accept(visitor);
    
    //interpreter::core::CInterpreter interpreter(parser, new_ptr(interpreter::core::CBootstrap)());
    
    //interpreter.run(program);
    
    // Clear AST for next test
    parser->clearAll();
}

BOOST_AUTO_TEST_SUITE_END()
