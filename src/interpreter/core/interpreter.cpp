#include "interpreter/core/interpreter.h"
#include "exceptions/runtime/wrongFormOfMainException.h"


namespace interpreter {

	namespace core {

		CInterpreter::CInterpreter(ptr(ParserWrapper) parser, ptr(bootstrap::CBootstrapStage2) bootstrap, ptr(memory::memspace::CDescriptorTable) table)
			: m_parser(parser),
			  m_bootstrap(bootstrap),
			  m_descriptorTable(table) {
		}

		void CInterpreter::execProgram(ptr(ast_program) node) {
			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				exec(node->getNodeAt(i));
			}
			ptr(mem_component) main = m_descriptorTable->getDescriptor(COMPO_MAIN_COMPONENT_NAME);
                        
                        ptr(mem_component) mainComponent = main->getServiceByName("new")->invoke()->getOwner();
                        mainComponent->getServiceByName(COMPO_MAIN_SERVICE_NAME)->invoke();
		}

		void CInterpreter::execDescriptor(ptr(ast_descriptor) node) {
			std::string name = node->getNameSymbol()->getStringValue();
			if (m_descriptorTable->descriptorFound(name)) {
				throw exceptions::semantic::CRedefinedDescriptorException(name);
			}
			m_descriptorTable->addDescriptor(m_bootstrap->bootstrapDescriptorComponent(node));
                }

                void CInterpreter::execCompound(ptr(ast_compound) node) {
                    ptr(CVariablesTable) context = new_ptr(CVariablesTable)();
                    for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
                        context->addVariable(node->getTemporaryAt(i)->getStringValue());
                    }
                    m_contextStack.push(context);
                    
                    for (size_t i = 0; i < node->getBodySize(); ++i) {
                        exec(node->getBodyNodeAt(i));
                    }
                    
                    m_contextStack.pop();
                }

                void CInterpreter::execAssignment(ptr(ast_assignment) node) {
                    std::string variable = node->getVariable()->getStringValue();
                    ptr(mem_port) port = m_contextStack.top()->getVariable(variable);
                    port = exec(node->getRightSide());
                    m_contextStack.top()->setVariable(variable, port);
                }

                ptr(mem_port) CInterpreter::execArithmeticOp(ptr(ast_binary) expr, type_operator op) {
                    u64 l = cast(mem_uint)(exec(expr->getOperand1())->getOwner())->getValue();
                    u64 r = cast(mem_uint)(exec(expr->getOperand2())->getOwner())->getValue();
                    u64 res = 0;
                    
                    switch (op) {
                        case type_operator::PLUS : {
                            res = l + r;
                        }
                        case type_operator::MINUS : {
                            res = l - r;
                        }
                        case type_operator::TIMES : {
                            res = l * r;
                        }
                        case type_operator::DIVISION : {
                            res = l / r;
                        }
                        default : {
                            // throw
                        }
                    }
                    return m_bootstrap->getUintComponent(res);
                }

                ptr(mem_port) CInterpreter::execLogicalOp(ptr(ast_binary) expr, type_operator op) {
                    bool l = cast(mem_bool)(exec(expr->getOperand1())->getOwner())->getValue();
                    bool r = cast(mem_bool)(exec(expr->getOperand2())->getOwner())->getValue();
                    bool res = 0;
                    
                    switch (op) {
                        case type_operator::LOGICAL_OR : {
                            res = l || r;
                        }
                        case type_operator::LOGICAL_AND : {
                            res = l && r;
                        }
                        default : {
                            // throw
                        }
                    }
                    return m_bootstrap->getBoolComponent(res);
                }

                ptr(mem_port) CInterpreter::execRelationalOp(ptr(ast_binary) expr, type_operator op) {
                    u64 l = cast(mem_uint)(exec(expr->getOperand1())->getOwner())->getValue();
                    u64 r = cast(mem_uint)(exec(expr->getOperand2())->getOwner())->getValue();
                    u64 res = 0;
                    
                    switch (op) {
                        case type_operator::EQUALITY : {
                            res = l == r;
                        }
                        case type_operator::NON_EQUALITY : {
                            res = l != r;
                        }
                        case type_operator::LESS : {
                            res = l < r;
                        }
                        case type_operator::LESS_OR_EQUAL : {
                            res = l <= r;
                        }
                        case type_operator::GREATER : {
                            res = l > r;
                        }
                        case type_operator::GREATER_OR_EQUAL : {
                            res = l >= r;
                        }
                        default : {
                            // throw
                        }
                    }
                    return m_bootstrap->getBoolComponent(res);
                }

                ptr(mem_port) CInterpreter::execServiceInvocation(ptr(ast_serviceinvocation) node) {
                    std::string receiver = node->getReceiverName()->getStringValue();
                    ptr(mem_port) port;
                    if (m_contextStack.top()->variableFound(receiver)) {
                        port = m_contextStack.top()->getVariable(receiver);
                    }
                    else {
                        port = m_descriptorTable->getDescriptor(receiver)->getPortByName("default");
                    }
                    
                    return port->getOwner()->getServiceByName(node->getSelectorName()->getStringValue())->invoke();
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
				break;
			}
                        /*------------------ Procedural ----------------------*/
                        case type_node::ASSIGNMENT_EXPRESSION : {
				execAssignment(cast(ast_assignment)(node));
				break;
			}
                        case type_node::CONSTANT : {
                                return m_bootstrap->getUintComponent(cast(ast_constant)(node)->getValue());
				break;
			}
                        case type_node::BOOLEAN : {
                                return m_bootstrap->getBoolComponent(cast(ast_boolean)(node)->getValue());
				break;
			}
                        case type_node::ADDITION_EXPRESSION : {
				return execArithmeticOp(cast(ast_addition)(node), type_operator::PLUS);
				break;
			}
                        case type_node::SUBTRACTION_EXPRESSION : {
				return execArithmeticOp(cast(ast_subtraction)(node), type_operator::MINUS);
				break;
			}
                        case type_node::MULTIPLICATION_EXPRESSION : {
				return execArithmeticOp(cast(ast_multiplication)(node), type_operator::TIMES);
				break;
			}
                        case type_node::DIVISION_EXPRESSION : {
				return execArithmeticOp(cast(ast_division)(node), type_operator::DIVISION);
				break;
			}
                        case type_node::LOGICAL_OR_EXPRESSION : {
				return execLogicalOp(cast(ast_or)(node), type_operator::LOGICAL_OR);
				break;
			}
                        case type_node::LOGICAL_AND_EXPRESSION : {
				return execLogicalOp(cast(ast_and)(node), type_operator::LOGICAL_AND);
				break;
			}
                        case type_node::EQUALITY_EXPRESSION : {
				return execRelationalOp(cast(ast_equality)(node), type_operator::EQUALITY);
				break;
			}
                        case type_node::NON_EQUALITY_EXPRESSION : {
				return execRelationalOp(cast(ast_nonequality)(node), type_operator::NON_EQUALITY);
				break;
			}
                        case type_node::LESS_EXPRESSION : {
				return execRelationalOp(cast(ast_less)(node), type_operator::LESS);
				break;
			}
                        case type_node::LESS_OR_EQUAL_EXPRESSION : {
				return execRelationalOp(cast(ast_lessorequal)(node), type_operator::LESS_OR_EQUAL);
				break;
			}
                        case type_node::GREATER_EXPRESSION : {
				return execRelationalOp(cast(ast_greater)(node), type_operator::GREATER);
				break;
			}
                        case type_node::GREATER_OR_EQUAL_EXPRESSION : {
				return execArithmeticOp(cast(ast_greaterorequal)(node), type_operator::GREATER_OR_EQUAL);
				break;
			}
                        /*------------------ Procedural ----------------------*/
			default : {
				throw exceptions::runtime::CUnknownAstNodeTypeException(typeName(node->getNodeType()));
			}
			}
                        return nullptr;
		}

		ptr(mem_port)  CInterpreter::execServiceCode(const std::string& code) {
			std::stringstream input;
			std::string serviceCode = code;
			input.str(serviceCode);

			m_parser->parse(serviceCode);

			ptr(ast_compound) body = m_parser->getServiceBody();

			return exec(body);
		}

		void CInterpreter::run(ptr(ast_program) ast) {
			exec(ast);
		}

	}

}