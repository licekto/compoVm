#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "logger/logger.h"

#include "definitions/allDefinitions.h"
#include "definitions/interpreterDefinitions.h"
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
#include "interpreter/core/bootstrap/bootstrapStage1.h"
#include "exceptions/semantic/wrongPortVisibiltyException.h"

BOOST_AUTO_TEST_SUITE(interpreterCompoComplexTest)

ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());
ptr(interpreter::memory::memspace::CDescriptorTable) table = new_ptr(interpreter::memory::memspace::CDescriptorTable)();

ptr(core_interpreter) initInterpreter() {
    ptr(interpreter::memory::memspace::CMemory) memory = new_ptr(interpreter::memory::memspace::CMemory)();
    ptr(core_bootstrap1) bootstrap1 = new_ptr(core_bootstrap1)(new_ptr(interpreter::core::CCoreModules)(parser), nullptr, memory);
    memory->setBootstrap1(bootstrap1);
    ptr(core_bootstrap2) bootstrap2 = new_ptr(core_bootstrap2)(bootstrap1);
    ptr(core_interpreter) interpreter = new_ptr(core_interpreter)(parser, bootstrap2, table);
    bootstrap1->setInterpreter(interpreter);
    return interpreter;
}

ptr(core_interpreter) interpreter = initInterpreter();

BOOST_AUTO_TEST_CASE(complexTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Add {\
        provides {\
            provAdd : { add(a, b); };\
        }\
        service add(a, b) {\
            return a + b;\
        }\
        service testAdd(a, b) {\
            return a + b + 2;\
        }\
    }\
    descriptor Sub {\
        provides {\
            provSub : { sub(a, b); };\
        }\
        service sub(a, b) {\
            return a - b;\
        }\
        service testSub(a, b) {\
            return a - b - 2;\
        }\
    }\
    descriptor Div {\
        provides {\
            provDiv : { div(a, b); };\
        }\
        service div(a, b) {\
            return a / b;\
        }\
        service testDiv(a, b) {\
            return a / b / 2;\
        }\
    }\
    descriptor Mul {\
        provides {\
            provMul : { mul(a, b); };\
        }\
        service mul(a, b) {\
            return a * b;\
        }\
        service testMul(a, b) {\
            return a * b * 2;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : { add(a, b); };\
            b : Sub;\
        }\
        externally requires {\
            c : { div(a, b); };\
            d : Mul;\
        }\
        internally provides {\
            e : { testInternal(a); };\
        }\
        externally provides {\
            g : { test(); };\
        }\
        architecture {\
            connect a to default@(Add.new());\
            connect b to default@(Sub.new());\
        }\
        service testInternal(var) {\
            return 1 + var;\
        }\
        service test() {\
            |tmp|\
            tmp := 1;\
            tmp := tmp + self.testInternal(2);\
            tmp := tmp * a.add(1, tmp);\
            tmp := tmp - b.testSub(1, tmp);\
            tmp := tmp + c.div(4, 2);\
            tmp := tmp - d.testMul(2, 3);\
            return tmp + a.add(1, 1);\
        }\
    }\
    descriptor Outer {\
        internally requires {\
            runPort : { test(); };\
        }\
        service run(inst) {\
            connect runPort to g@inst;\
            connect c@inst to default@(Div.new());\
            connect d@inst to default@(Mul.new());\
            return runPort.test();\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i outer|\
            i := Inst.new();\
            outer := Outer.new();\
            return outer.run(i);\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_int)(inst)->getValue(), 33);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
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
            return System.getRand(seed);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |c|\
            c := Calc.new();\
            connect randGen@c to default@(RandomGen.new());\
            c.rand();\
            return c.mul(3,c.pow(2,3));\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_int)(inst)->getValue(), 24);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
