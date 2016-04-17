#include "interpreter/core/interpreter.h"
#include "exceptions/runtime/wrongFormOfMainException.h"
#include "exceptions/execution/returnException.h"


namespace interpreter {

	namespace core {

		CInterpreter::CInterpreter(ptr(ParserWrapper) parser,
                                           ptr(bootstrap::CBootstrapStage2) bootstrap,
                                           ptr(memory::memspace::CDescriptorTable) table)
			: m_parser(parser),
			  m_bootstrap(bootstrap),
			  m_descriptorTable(table){
		}

		ptr(mem_port) CInterpreter::execProgram(ptr(ast_program) node) {
			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				exec(node->getNodeAt(i));
			}
			ptr(mem_component) main = m_descriptorTable->getDescriptor(COMPO_MAIN_COMPONENT_NAME);
                        
                        ptr(mem_component) mainComponent = main->getServiceByName("new")->invoke()->getOwner();
                        m_serviceContextStack.push(new_ptr(CContext)());
                        return mainComponent->getServiceByName(COMPO_MAIN_SERVICE_NAME)->invoke();
		}

		void CInterpreter::execDescriptor(ptr(ast_descriptor) node) {
			std::string name = node->getNameSymbol()->getStringValue();
			if (m_descriptorTable->descriptorFound(name)) {
				throw exceptions::semantic::CRedefinedDescriptorException(name);
			}
			m_descriptorTable->addDescriptor(m_bootstrap->bootstrapDescriptorComponent(node));
                }

                void CInterpreter::execCompound(ptr(ast_compound) node) {
                    m_serviceContextStack.top()->pushContext(node);
                    
                    for (size_t i = 0; i < node->getBodySize(); ++i) {
                        exec(node->getBodyNodeAt(i));
                    }
                    
                    m_serviceContextStack.top()->popContext();
                }

                void CInterpreter::execAssignment(ptr(ast_assignment) node) {
                    std::string variable = node->getVariable()->getStringValue();
                    ptr(mem_port) port = m_serviceContextStack.top()->getVariable(variable);
                    port = exec(node->getRightSide());
                    m_serviceContextStack.top()->setVariable(variable, port);
                }

                ptr(mem_port) CInterpreter::execArithmeticOp(ptr(ast_binary) expr, type_operator op) {
                    i64 l = cast(mem_int)(exec(expr->getOperand1())->getOwner())->getValue();
                    i64 r = cast(mem_int)(exec(expr->getOperand2())->getOwner())->getValue();
                    i64 res = 0;
                    
                    switch (op) {
                        case type_operator::PLUS : {
                            res = l + r;
                            break;
                        }
                        case type_operator::MINUS : {
                            res = l - r;
                            break;
                        }
                        case type_operator::TIMES : {
                            res = l * r;
                            break;
                        }
                        case type_operator::DIVISION : {
                            res = l / r;
                            break;
                        }
                        default : {
                            // throw
                        }
                    }
                    return m_bootstrap->getIntComponent(res);
                }

                ptr(mem_port) CInterpreter::execLogicalOp(ptr(ast_binary) expr, type_operator op) {
                    bool l = cast(mem_bool)(exec(expr->getOperand1())->getOwner())->getValue();
                    bool r = cast(mem_bool)(exec(expr->getOperand2())->getOwner())->getValue();
                    bool res = 0;
                    
                    switch (op) {
                        case type_operator::LOGICAL_OR : {
                            res = l || r;
                            break;
                        }
                        case type_operator::LOGICAL_AND : {
                            res = l && r;
                            break;
                        }
                        default : {
                            // throw
                        }
                    }
                    return m_bootstrap->getBoolComponent(res);
                }

                ptr(mem_port) CInterpreter::execRelationalOp(ptr(ast_binary) expr, type_operator op) {
                    i64 l = cast(mem_int)(exec(expr->getOperand1())->getOwner())->getValue();
                    i64 r = cast(mem_int)(exec(expr->getOperand2())->getOwner())->getValue();
                    bool res = 0;
                    
                    switch (op) {
                        case type_operator::EQUALITY : {
                            res = l == r;
                            break;
                        }
                        case type_operator::NON_EQUALITY : {
                            res = l != r;
                            break;
                        }
                        case type_operator::LESS : {
                            res = l < r;
                            break;
                        }
                        case type_operator::LESS_OR_EQUAL : {
                            res = l <= r;
                            break;
                        }
                        case type_operator::GREATER : {
                            res = l > r;
                            break;
                        }
                        case type_operator::GREATER_OR_EQUAL : {
                            res = l >= r;
                            break;
                        }
                        default : {
                            // throw
                        }
                    }
                    return m_bootstrap->getBoolComponent(res);
                }

                ptr(mem_port) CInterpreter::execServiceInvocation(ptr(ast_serviceinvocation) node) {
                    std::string receiver = node->getReceiverName()->getStringValue();
                    std::string selector = node->getSelectorName()->getStringValue();
                    u64 index = 0;
                    if (node->getIndex().use_count() && node->getIndex()->getNodeType() == type_node::SYMBOL) {
                        std::string var = cast(ast_symbol)(node->getIndex())->getStringValue();
                        index = cast(mem_int)(m_serviceContextStack.top()->getVariable(var)->getOwner())->getValue();
                    }
                    else if (node->getIndex().use_count() && node->getIndex()->getNodeType() == type_node::CONSTANT) {
                        index = cast(ast_constant)(node->getIndex())->getValue();
                    }
                    ptr(mem_port) port;
                    if (m_serviceContextStack.top()->getTopContext()->variableFound(receiver)) {
                        port = m_serviceContextStack.top()->getVariable(receiver);
                    }
                    else {
                        port = m_descriptorTable->getDescriptor(receiver)->getPortByName("default");
                    }
                    
                    if (node->getParameters()->getNodeType() == type_node::SERVICE_SIGNATURE) {
                        ptr(ast_servicesignature) sign = cast(ast_servicesignature)(node->getParameters());
                        for (size_t i = 0; i < sign->getParamsSize(); ++i) {
                            type_node t = sign->getParamAt(i)->getNodeType();
                            ptr(mem_port) connectedPort;
                            switch(t) {
                                case type_node::SYMBOL : {
                                    connectedPort = m_serviceContextStack.top()->getVariable(cast(ast_symbol)(sign->getParamAt(i))->getStringValue());
                                    break;
                                }
                                case type_node::STRING_LITERAL : {
                                    connectedPort = m_bootstrap->getStringComponent(cast(ast_string)(sign->getParamAt(i))->getValue());
                                    break;
                                }
                                case type_node::CONSTANT : {
                                    connectedPort = m_bootstrap->getIntComponent(cast(ast_constant)(sign->getParamAt(i))->getValue());
                                    break;
                                }
                                case type_node::BOOLEAN : {
                                    connectedPort = m_bootstrap->getBoolComponent(cast(ast_boolean)(sign->getParamAt(i))->getValue());
                                    break;
                                }
                                case type_node::SERVICE_INVOCATION : {
                                    connectedPort = exec(sign->getParamAt(i));
                                    break;
                                }
                                default : {
                                    // throw
                                }
                                port->getOwner()->getPortByName("args")->connectPort(connectedPort);
                            }
                        }
                    }
                    else if (node->getParameters()->getNodeType() == type_node::SERVICE_INVOCATION) {
                        port->getOwner()->getPortByName("args")->connectPort(exec(node->getParameters()));
                    }
                    else {
                        // throw
                    }
                    
                    return port->invokeByName(selector, index);
                }

		ptr(mem_port)  CInterpreter::exec(ptr(ast_node) node) {
			switch (node->getNodeType()) {
			case type_node::PROGRAM : {
				execProgram(cast(ast_program)(node));
				break;
			}
			case type_node::DESCRIPTOR : {
				execDescriptor(cast(ast_descriptor)(node));
				break;
			}
                        case type_node::COMPOUND_BODY : {
				execCompound(cast(ast_compound)(node));
				break;
			}
                        case type_node::SERVICE_INVOCATION : {
				return execServiceInvocation(cast(ast_serviceinvocation)(node));
			}
                        /*------------------ Procedural ----------------------*/
                        case type_node::ASSIGNMENT_EXPRESSION : {
				execAssignment(cast(ast_assignment)(node));
				break;
			}
                        case type_node::SYMBOL : {
                                return m_serviceContextStack.top()->getVariable(cast(ast_symbol)(node)->getStringValue());
			}
                        case type_node::CONSTANT : {
                                return m_bootstrap->getIntComponent(cast(ast_constant)(node)->getValue());
			}
                        case type_node::BOOLEAN : {
                                return m_bootstrap->getBoolComponent(cast(ast_boolean)(node)->getValue());
			}
                        case type_node::RETURN : {
                                throw exceptions::execution::CReturnException(exec(cast(ast_return)(node)->getExpression()));
			}
                        case type_node::PARENS : {
                                return exec(cast(ast_parens)(node)->getExpression());
			}
                        case type_node::ADDITION_EXPRESSION : {
				return execArithmeticOp(cast(ast_addition)(node), type_operator::PLUS);
			}
                        case type_node::SUBTRACTION_EXPRESSION : {
				return execArithmeticOp(cast(ast_subtraction)(node), type_operator::MINUS);
			}
                        case type_node::MULTIPLICATION_EXPRESSION : {
				return execArithmeticOp(cast(ast_multiplication)(node), type_operator::TIMES);
			}
                        case type_node::DIVISION_EXPRESSION : {
				return execArithmeticOp(cast(ast_division)(node), type_operator::DIVISION);
			}
                        case type_node::LOGICAL_OR_EXPRESSION : {
				return execLogicalOp(cast(ast_or)(node), type_operator::LOGICAL_OR);
			}
                        case type_node::LOGICAL_AND_EXPRESSION : {
				return execLogicalOp(cast(ast_and)(node), type_operator::LOGICAL_AND);
			}
                        case type_node::EQUALITY_EXPRESSION : {
				return execRelationalOp(cast(ast_equality)(node), type_operator::EQUALITY);
			}
                        case type_node::NON_EQUALITY_EXPRESSION : {
				return execRelationalOp(cast(ast_nonequality)(node), type_operator::NON_EQUALITY);
			}
                        case type_node::LESS_EXPRESSION : {
				return execRelationalOp(cast(ast_less)(node), type_operator::LESS);
			}
                        case type_node::LESS_OR_EQUAL_EXPRESSION : {
				return execRelationalOp(cast(ast_lessorequal)(node), type_operator::LESS_OR_EQUAL);
			}
                        case type_node::GREATER_EXPRESSION : {
				return execRelationalOp(cast(ast_greater)(node), type_operator::GREATER);
			}
                        case type_node::GREATER_OR_EQUAL_EXPRESSION : {
				return execRelationalOp(cast(ast_greaterorequal)(node), type_operator::GREATER_OR_EQUAL);
			}
                        /*------------------ Procedural ----------------------*/
			default : {
				throw exceptions::runtime::CUnknownAstNodeTypeException(typeName(node->getNodeType()));
			}
			}
                        return nullptr;
		}

		ptr(mem_port)  CInterpreter::execServiceCode(const std::string& code, ptr(CContext) context) {
			std::stringstream input;
			std::string serviceCode = code;
			input.str(serviceCode);

			m_parser->parse(serviceCode);

			ptr(ast_compound) body = m_parser->getServiceBody();
                        ptr(mem_port) ret;
                        
                        if (!context.use_count()) {
                            context = new_ptr(CContext)();
                        }
                        m_serviceContextStack.push(context);
                        
                        try {
                            exec(body);
                        }
                        catch (exceptions::execution::CReturnException& ex) {
                            ret = ex.getPort();
                        }
                        m_serviceContextStack.pop();
                        
                        return ret;
                }

		ptr(mem_port) CInterpreter::run(ptr(ast_program) ast) {
			return exec(ast);
		}

	}

}