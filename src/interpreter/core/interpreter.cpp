#include "interpreter/core/interpreter.h"
#include "exceptions/runtime/variableNotFoundException.h"
#include "exceptions/execution/breakException.h"
#include "exceptions/execution/continueException.h"
#include "exceptions/runtime/unknownValueComponentTypeException.h"
#include "exceptions/runtime/wrongStringOperationException.h"


namespace interpreter {

	namespace core {

		CInterpreter::CInterpreter(ptr(ParserWrapper) parser,
		                           ptr(bootstrap::CBootstrapStage2) bootstrap,
		                           ptr(memory::memspace::CDescriptorTable) table)
			: m_parser(parser),
			  m_bootstrap(bootstrap),
			  m_descriptorTable(table) {
		}

		void CInterpreter::boot() {
			m_descriptorTable->addDescriptor(m_bootstrap->bootstrapSystemComponent());
		}

		ptr(mem_port) CInterpreter::execProgram(ptr(ast_program) node) {
			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				exec(node->getNodeAt(i));
			}
			ptr(mem_component) main = m_descriptorTable->getDescriptor(COMPO_MAIN_COMPONENT_NAME);

			ptr(mem_component) mainComponent = main->getServiceByName("new")->invoke()->getOwner();
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
			ptr(mem_port) port = m_serviceContextStack.top()->getVariable(variable, 0, true);
			port = exec(node->getRightSide());
			m_serviceContextStack.top()->setVariableAssignment(variable, port);
		}

		std::string CInterpreter::getStringRepresentation(ptr(mem_value) val) {
			switch(val->getType()) {
			case type_values::STRING : {
				return cast(mem_string)(val)->getValue();
			}
			case type_values::INTEGER : {
				return std::to_string(cast(mem_int)(val)->getValue());
			}
			case type_values::BOOL : {
				return cast(mem_bool)(val)->getValue() ? "true" : "false";
			}
			default : {
				throw exceptions::runtime::CUnknownValueComponentTypeException();
			}
			}
		}

		ptr(mem_port) CInterpreter::execArithmeticOp(ptr(ast_binary) expr, type_operator op) {
			ptr(mem_value) val1 = cast(mem_value)(exec(expr->getOperand1())->getOwner());
			ptr(mem_value) val2 = cast(mem_value)(exec(expr->getOperand2())->getOwner());

			if (val1->getType() == type_values::STRING || val2->getType() == type_values::STRING) {
				if (op != type_operator::PLUS) {
					throw exceptions::runtime::CWrongStringOperationException();
				}
				return m_bootstrap->getStringComponent(getStringRepresentation(val1) + getStringRepresentation(val2));
			}

			i64 l = cast(mem_int)(val1)->getValue();
			i64 r = cast(mem_int)(val2)->getValue();
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
				throw exceptions::runtime::CUnknownOperatorTypeException();
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
				throw exceptions::runtime::CUnknownOperatorTypeException();
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
				throw exceptions::runtime::CUnknownOperatorTypeException();
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
			} else if (node->getIndex().use_count() && node->getIndex()->getNodeType() == type_node::CONSTANT) {
				index = cast(ast_constant)(node->getIndex())->getValue();
			}

			ptr(mem_port) port;
			try {
				port = m_serviceContextStack.top()->getVariable(receiver, index);
			} catch (const exceptions::runtime::CVariableNotFoundException& ex) {
				port = m_descriptorTable->getDescriptor(receiver)->getPortByName("default");
			}
			ptr(mem_port) delegatedPort = port->getOwner()->getPortByName("args");
			while (delegatedPort->getDelegatedPort().use_count()) {
				delegatedPort = delegatedPort->getDelegatedPort();
			}
			std::vector<ptr(mem_port)> oldArgs;
			for (size_t i = 0; i < delegatedPort->getOwner()->getPortByName("args")->getConnectedPortsNumber(); ++i) {
				oldArgs.push_back(delegatedPort->getOwner()->getPortByName("args")->getConnectedPortAt(i));
			}
			delegatedPort->getOwner()->getPortByName("args")->disconnectAll();
                        
			if (node->getParameters()->getNodeType() == type_node::SERVICE_SIGNATURE) {
				ptr(ast_servicesignature) sign = cast(ast_servicesignature)(node->getParameters());
				std::vector<ptr(mem_port)> connectedPorts;
				for (size_t i = 0; i < sign->getParamsSize(); ++i) {
					connectedPorts.push_back(exec(sign->getParamAt(i)));
				}
				for (size_t i = 0; i < connectedPorts.size(); ++i) {
					port->getOwner()->getPortByName("args")->connectPort(connectedPorts.at(i));
				}
			} else if (node->getParameters()->getNodeType() == type_node::SERVICE_INVOCATION) {
				port->getOwner()->getPortByName("args")->connectPort(exec(node->getParameters()));
			} else {
				throw exceptions::runtime::CWrongServiceInvocationParameterTypeException(node->getParameters()->getNodeType());
			}

			std::string caller = m_serviceContextStack.top()->getServiceName();
			ptr(mem_port) ret = port->invokeByName(caller, receiver, selector, index);

			for (size_t i = 0; i < port->getOwner()->getPortByName("args")->getConnectedPortsNumber(); ++i) {
				port->getOwner()->getPortByName("args")->disconnectPortAt(i);
			}

			for (ptr(mem_port) oldPort : oldArgs) {
				delegatedPort->getOwner()->getPortByName("args")->connectPort(oldPort);
			}

			return ret;
		}

		ptr(mem_port) CInterpreter::execConnection(ptr(ast_connection) node) {
			ptr(ast_portaddress) source = node->getSourcePortIdentification();
			ptr(ast_portaddress) destination = node->getDestinationPortIdentification();

			ptr(mem_port) srcComponent = exec(source->getComponent());
			ptr(mem_port) srcPort = srcComponent->getOwner()->getPortByName(source->getPortName()->getStringValue());

			ptr(mem_port) dstComponent = exec(destination->getComponent());
			ptr(mem_port) dstPort = dstComponent->getOwner()->getPortByName(destination->getPortName()->getStringValue());

			checkBindAddresses(srcPort, dstPort);

			bool collection = cast(mem_bool)(srcPort->getPort()->getPortByName("isCollection")->getConnectedPortAt(0)->getOwner())->getValue();
			i64 index = 0;

			if (!collection) {
				srcPort->disconnectPortAt(0);
			} else {
				index = srcPort->getConnectedPortsNumber();
			}

			srcPort->connectPort(dstPort);

			return m_bootstrap->getIntComponent(index);
		}

		void CInterpreter::execDisconnection(ptr(ast_disconnection) node) {
			ptr(ast_portaddress) source = node->getSourcePortIdentification();
			ptr(ast_portaddress) destination = node->getDestinationPortIdentification();

			ptr(mem_port) srcComponent = exec(source->getComponent());
			ptr(mem_port) srcPort = srcComponent->getOwner()->getPortByName(source->getPortName()->getStringValue());

			ptr(mem_port) dstComponent = exec(destination->getComponent());
			ptr(mem_port) dstPort = dstComponent->getOwner()->getPortByName(destination->getPortName()->getStringValue());

			checkBindAddresses(srcPort, dstPort);

			srcPort->disconnectPortAt(0);
			dstPort->disconnectPortAt(0);
                }

                ptr(mem_port) CInterpreter::execSizeof(ptr(ast_sizeof) node) {
                    std::string portName = node->getParamName()->getStringValue();
                    i64 value = m_serviceContextStack.top()->getContextComponent()->getPortByName(portName)->getConnectedPortsNumber();
                    return m_bootstrap->getIntComponent(value);
                }

		void CInterpreter::checkBindAddresses(ptr(mem_port) srcPort, ptr(mem_port) dstPort) {
			bool def = srcPort->getName() != "default" && dstPort->getName() != "default";
			bool vis1 = srcPort->getVisibility() == type_visibility::INTERNAL && m_serviceContextStack.top()->getContextComponent()->getTopParent().get() != srcPort->getOwner()->getTopParent().get();
			bool vis2 = dstPort->getVisibility() == type_visibility::INTERNAL && m_serviceContextStack.top()->getContextComponent()->getTopParent().get() != dstPort->getOwner()->getTopParent().get();
			bool role = srcPort->getRole() == dstPort->getRole();

			if (def && (vis1 || vis2 || role)) {
				std::string portNames = srcPort->getName() + " and " + dstPort->getName();
				throw exceptions::semantic::CWrongPortVisibilityException(portNames);
			}
		}

		void CInterpreter::execFor(ptr(ast_for) node) {
			exec(node->getInitExpression());
			while (cast(mem_bool)(exec(node->getCondition())->getOwner())->getValue()) {
				try {
					exec(node->getBody());
				} catch (const exceptions::execution::CBreakException& ex) {
					break;
				} catch (const exceptions::execution::CContinueException& ex) {
				}
				exec(node->getIncrement());
			}
		}

		void CInterpreter::execWhile(ptr(ast_while) node) {
			while (cast(mem_bool)(exec(node->getCondition())->getOwner())->getValue()) {
				try {
					exec(node->getBody());
				} catch (const exceptions::execution::CBreakException& ex) {
					break;
				} catch (const exceptions::execution::CContinueException& ex) {
				}
			}
		}

		void CInterpreter::execIf(ptr(ast_if) node) {
			if (cast(mem_bool)(exec(node->getCondition())->getOwner())->getValue()) {
				exec(node->getIfBody());
			} else if (node->getElseBody().use_count()) {
				exec(node->getElseBody());
			}
		}

		ptr(mem_port)  CInterpreter::exec(ptr(ast_node) node) {
			switch (node->getNodeType()) {
			case type_node::PROGRAM : {
				return execProgram(cast(ast_program)(node));
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
			case type_node::CONNECTION : {
				return execConnection(cast(ast_connection)(node));
			}
			case type_node::DISCONNECTION : {
				execDisconnection(cast(ast_disconnection)(node));
				break;
			}
                        case type_node::SIZEOF : {
				return execSizeof(cast(ast_sizeof)(node));
			}
			/*------------------ Procedural ----------------------*/
			case type_node::FOR : {
				execFor(cast(ast_for)(node));
				break;
			}
			case type_node::WHILE : {
				execWhile(cast(ast_while)(node));
				break;
			}
			case type_node::BREAK : {
				throw exceptions::execution::CBreakException();
			}
			case type_node::CONTINUE : {
				throw exceptions::execution::CContinueException();
			}
			case type_node::IF : {
				execIf(cast(ast_if)(node));
				break;
			}
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
			case type_node::STRING_LITERAL : {
				return m_bootstrap->getStringComponent(cast(ast_string)(node)->getValue());
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
			} catch (exceptions::execution::CReturnException& ex) {
				ret = ex.getPort();
			}
			m_serviceContextStack.pop();

			return ret;
		}

		ptr(mem_port) CInterpreter::execService(const std::string& receiver, const std::string& selector) {
                        if (!m_descriptorTable->descriptorFound(receiver)) {
                            throw exceptions::semantic::CUndefinedDescriptorException(receiver);
                        }
			ptr(mem_component) descriptor = m_descriptorTable->getDescriptor(receiver);
			return descriptor->getServiceByName(selector)->invoke();
		}

		ptr(mem_port) CInterpreter::run(ptr(ast_program) ast) {
			boot();
			return exec(ast);
		}

	}

}