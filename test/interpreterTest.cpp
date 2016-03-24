#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "ast/visitor/semanticCheckVisitor.h"
#include "ast/semantic/globalDescriptorsTable.h"
#include "exceptions/semantic/emptyProgramException.h"
#include "exceptions/semantic/undefinedDescriptorException.h"
#include "exceptions/semantic/undefinedInterfaceException.h"
#include "exceptions/semantic/redefinedDescriptorException.h"
#include "exceptions/semantic/redefinedInterfaceException.h"
#include "exceptions/semantic/wrongBaseTypeException.h"
#include "exceptions/semantic/bidirectionalPortNotSupportedException.h"
#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"

BOOST_AUTO_TEST_SUITE(interpreterTest)


// Global parser for testing purposes
ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CGlobalDescriptorTable)());

BOOST_AUTO_TEST_CASE(basicTest) {
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
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    
    ptr(ast::visitors::CSemanticCheckVisitor) visitor = new_ptr(ast::visitors::CSemanticCheckVisitor)(parser->getDescriptorTable());

    program->accept(visitor);
    
    ptr(interpreter::core::CCoreModules) loader = new_ptr(interpreter::core::CCoreModules)(parser);
    
    interpreter::core::CInterpreter interpreter(program, parser->getDescriptorTable(), loader);
    
    interpreter.run();
    
    // Clear AST for next test
    parser->clearAll();
}

BOOST_AUTO_TEST_SUITE_END()
