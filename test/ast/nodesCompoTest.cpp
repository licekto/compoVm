#include <memory>

#include <boost/test/unit_test.hpp>

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"

BOOST_AUTO_TEST_SUITE(nodesCompoTest)

BOOST_AUTO_TEST_CASE(symbolTest) {
    // Original symbol creation
    ast_symbol symbol("Symbol");
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    
    // Copy ctor test
    ast_symbol symbolCopy1(symbol);
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbolCopy1.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy1.getStringValue());
    
    // Copy assignment operator test
    ast_symbol symbolCopy2 = symbol;
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbolCopy2.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy2.getStringValue());
    
    // Move constructor test
    ast_symbol symbolNew1(std::move(symbol));
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("", symbol.getStringValue());
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbolCopy1.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy1.getStringValue());
    
    // Move assignment operator test
    ast_symbol symbolNew2 = std::move(symbolNew1);
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbolNew1.getNodeType());
    BOOST_CHECK_EQUAL("", symbolNew1.getStringValue());
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbolNew2.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolNew2.getStringValue());
}

/*
BOOST_AUTO_TEST_CASE(portTest) {
    // Original port creation
    ast::nodes::compo::CPort port(types::portType::UNIVERSAL, new_ptr(ast_symbol)("port"), true);
    BOOST_CHECK_EQUAL(types::nodeType::PORT, port.getNodeType());
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomicity());
    
    // Copy ctor test
    ast::nodes::compo::CPort portCopy1(port);
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomicity());
    BOOST_CHECK_EQUAL("port", portCopy1.getName());
    BOOST_CHECK(portCopy1.getAtomicity());
    
    // Copy assignment operator test
    ast::nodes::compo::CPort portCopy2 = port;
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomicity());
    BOOST_CHECK_EQUAL("port", portCopy2.getName());
    BOOST_CHECK(portCopy2.getAtomicity());
    
    // Move constructor test
    ast::nodes::compo::CPort portMoved1(std::move(port));
    BOOST_CHECK_EQUAL("", port.getName());
    BOOST_CHECK(port.getAtomicity());
    BOOST_CHECK_EQUAL("port", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomicity());
    
    // Move assignment operator test
    ast::nodes::compo::CPort portMoved2 = std::move(portMoved1);
    BOOST_CHECK_EQUAL("", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomicity());
    BOOST_CHECK_EQUAL("port", portMoved2.getName());
    BOOST_CHECK(portMoved2.getAtomicity());
}
*/

BOOST_AUTO_TEST_CASE(injectedPortTest) {
    // Original port creation
    ast_injectedport port(new_ptr(ast_symbol)("port"), true, new_ptr(ast_symbol)("injectingPort"));
    BOOST_CHECK_EQUAL(types::nodeType::INJECTED_PORT, port.getNodeType());
    BOOST_CHECK_EQUAL("port", port.getNameSymbol()->getStringValue());
    BOOST_CHECK(port.getAtomicity());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith()->getStringValue());
    
    // Copy ctor test
    ast_injectedport portCopy1(port);
    BOOST_CHECK_EQUAL("port", port.getNameSymbol()->getStringValue());
    BOOST_CHECK(port.getAtomicity());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith()->getStringValue());
    BOOST_CHECK_EQUAL("port", portCopy1.getNameSymbol()->getStringValue());
    BOOST_CHECK(portCopy1.getAtomicity());
    BOOST_CHECK_EQUAL("injectingPort", portCopy1.getInjectedWith()->getStringValue());
    
    // Copy assignment operator test
    ast_injectedport portCopy2 = port;
    BOOST_CHECK_EQUAL("port", port.getNameSymbol()->getStringValue());
    BOOST_CHECK(port.getAtomicity());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith()->getStringValue());
    BOOST_CHECK_EQUAL("port", portCopy2.getNameSymbol()->getStringValue());
    BOOST_CHECK(portCopy2.getAtomicity());
    BOOST_CHECK_EQUAL("injectingPort", portCopy2.getInjectedWith()->getStringValue());
    
    // Move constructor test
    ast_injectedport portMoved1(std::move(port));
    BOOST_CHECK(port.getAtomicity());
    BOOST_CHECK_EQUAL("port", portMoved1.getNameSymbol()->getStringValue());
    BOOST_CHECK(portMoved1.getAtomicity());
    BOOST_CHECK_EQUAL("injectingPort", portMoved1.getInjectedWith()->getStringValue());
    
    // Move assignment operator test
    ast_injectedport portMoved2 = std::move(portMoved1);
    BOOST_CHECK(portMoved1.getAtomicity());
    BOOST_CHECK_EQUAL("port", portMoved2.getNameSymbol()->getStringValue());
    BOOST_CHECK(portMoved2.getAtomicity());
    BOOST_CHECK_EQUAL("injectingPort", portMoved2.getInjectedWith()->getStringValue());
}

/*
BOOST_AUTO_TEST_CASE(serviceTest) {
    // Params vector preparation
    std::vector<ptr(ast::nodes::CNode)> params;
    params.push_back(new_ptr(ast_symbol)("param1"));
    params.push_back(new_ptr(ast_symbol)("param2"));
    
    ptr(ast_servicesignature) signature = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("service"), params);
    
    // Body vector preparation
    std::vector<ptr(ast::nodes::CNode)> body;
    body.push_back(new_ptr(ast_symbol)("Expr1"));
    
    // Temporaries vector preparation
    std::vector<ptr(ast_symbol)> temporaries;
    temporaries.push_back(new_ptr(ast_symbol)("Temp1"));
    
    // Compound body preparation
    ptr(ast_compound) compoundBody = new_ptr(ast_compound)(temporaries, body);
    
    ptr(ast_string) body = "{}";
    
    // Service creation
    ast_service service(signature, body);
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(service.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(service.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", cast(ast_symbol)(service.getTemporaryAt(0))->getStringValue());
    
    // Copy constructor test
    ast_service serviceCopy1(service);
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, serviceCopy1.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceCopy1.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, serviceCopy1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(serviceCopy1.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(serviceCopy1.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(serviceCopy1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy1.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", cast(ast_symbol)(serviceCopy1.getTemporaryAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(service.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(service.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", cast(ast_symbol)(service.getTemporaryAt(0))->getStringValue());
    
    // Copy assignment operator test
    ast_service serviceCopy2 = service;
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, serviceCopy2.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceCopy2.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, serviceCopy2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(serviceCopy2.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(serviceCopy2.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(serviceCopy2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy2.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", cast(ast_symbol)(serviceCopy2.getTemporaryAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(service.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(service.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", cast(ast_symbol)(service.getTemporaryAt(0))->getStringValue());
    
    // Move constructor test
    ast_service serviceNew1(std::move(service));
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, serviceNew1.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceNew1.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, serviceNew1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(serviceNew1.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(serviceNew1.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(serviceNew1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew1.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", cast(ast_symbol)(serviceNew1.getTemporaryAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL(0, service.getParamsSize());
    BOOST_CHECK_EQUAL(0, service.getBodySize());
    BOOST_CHECK_EQUAL(0, service.getTemporariesSize());
    
    // Copy assignment operator test
    ast_service serviceNew2 = std::move(serviceNew1);
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, serviceNew2.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceNew2.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, serviceNew2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(serviceNew2.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(serviceNew2.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(serviceNew2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew2.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", cast(ast_symbol)(serviceNew2.getTemporaryAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, serviceNew1.getNodeType());
    BOOST_CHECK_EQUAL(0, serviceNew1.getParamsSize());
    BOOST_CHECK_EQUAL(0, serviceNew1.getBodySize());
    BOOST_CHECK_EQUAL(0, serviceNew1.getTemporariesSize());
}
*/

BOOST_AUTO_TEST_CASE(constraintTest) {
    // Params vector preparation
    std::vector<ptr(ast::nodes::CNode)> params;
    params.push_back(new_ptr(ast_symbol)("param1"));
    params.push_back(new_ptr(ast_symbol)("param2"));
    
    ptr(ast_servicesignature) signature = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("constraint"), params);
    
    // Body vector preparation
    std::vector<ptr(ast::nodes::CNode)> body;
    body.push_back(new_ptr(ast_symbol)("Expr1"));
    
    // Compound body preparation
    ptr(ast_compound) compoundBody = new_ptr(ast_compound)(std::vector<ptr(ast_symbol)>(0), body);
    
    // Constraint creation
    ast_constraint constraint(signature, compoundBody);
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("constraint", constraint.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(constraint.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(constraint.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Copy constructor test
    ast_constraint constraintCopy1(constraint);
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraintCopy1.getNodeType());
    BOOST_CHECK_EQUAL("constraint", constraintCopy1.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, constraintCopy1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(constraintCopy1.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(constraintCopy1.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(constraintCopy1.getBodyNodeAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("constraint", constraint.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(constraint.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(constraint.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Copy assignment operator test
    ast_constraint constraingCopy2 = constraint;
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraingCopy2.getNodeType());
    BOOST_CHECK_EQUAL("constraint", constraingCopy2.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, constraingCopy2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(constraingCopy2.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(constraingCopy2.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, constraingCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(constraingCopy2.getBodyNodeAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("constraint", constraint.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(constraint.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(constraint.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Move constructor test
    ast_constraint constraintNew1(std::move(constraint));
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraintNew1.getNodeType());
    BOOST_CHECK_EQUAL("constraint", constraintNew1.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, constraintNew1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(constraintNew1.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(constraintNew1.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(constraintNew1.getBodyNodeAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL(0, constraint.getParamsSize());
    BOOST_CHECK_EQUAL(0, constraint.getBodySize());
    
    // Copy assignment operator test
    ast_constraint constraintNew2 = std::move(constraintNew1);
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraintNew2.getNodeType());
    BOOST_CHECK_EQUAL("constraint", constraintNew2.getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL(2, constraintNew2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(constraintNew2.getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(constraintNew2.getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(constraintNew2.getBodyNodeAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraintNew1.getNodeType());
    BOOST_CHECK_EQUAL(0, constraintNew1.getParamsSize());
    BOOST_CHECK_EQUAL(0, constraintNew1.getBodySize());
}


BOOST_AUTO_TEST_CASE(descriptorTest) {
    // Descriptor creation
    ptr(ast_descriptor) descriptor = new_ptr(ast_descriptor)(new_ptr(ast_symbol)("descriptorName"), new_ptr(ast_symbol)("descriptorExtends"));
    TEST_DESCRIPTOR(descriptor, "descriptorName", "descriptorExtends", 0, 0, 0);
    /*
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", cast(ast_symbol)(descriptor.getBodyNodeAt(1))->getStringValue());
    */
    /*
    // Copy constructor test
    ast_descriptor descriptorCopy1(descriptor);
    BOOST_CHECK_EQUAL("descriptorName", descriptorCopy1.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorCopy1.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(descriptorCopy1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", cast(ast_symbol)(descriptorCopy1.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", cast(ast_symbol)(descriptor.getBodyNodeAt(1))->getStringValue());
    
    // Copy assignment operator test
    ast_descriptor descriptorCopy2 = descriptor;
    BOOST_CHECK_EQUAL("descriptorName", descriptorCopy2.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorCopy2.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(descriptorCopy2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", cast(ast_symbol)(descriptorCopy2.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", cast(ast_symbol)(descriptor.getBodyNodeAt(1))->getStringValue());
    
    // Move constructor test
    ast_descriptor descriptorNew1(std::move(descriptor));
    BOOST_CHECK_EQUAL("descriptorName", descriptorNew1.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorNew1.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(descriptorNew1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", cast(ast_symbol)(descriptorNew1.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("", descriptor.getName());
    BOOST_CHECK_EQUAL("", descriptor.getExtends());
    BOOST_CHECK_EQUAL(0, descriptor.getBodySize());
    
    // Move assignment operator test
    ast_descriptor descriptorNew2 = std::move(descriptorNew1);
    BOOST_CHECK_EQUAL("descriptorName", descriptorNew2.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorNew2.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", cast(ast_symbol)(descriptorNew2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", cast(ast_symbol)(descriptorNew2.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("", descriptorNew1.getName());
    BOOST_CHECK_EQUAL("", descriptorNew1.getExtends());
    BOOST_CHECK_EQUAL(0, descriptorNew1.getBodySize());
     * */
}

BOOST_AUTO_TEST_SUITE_END()
