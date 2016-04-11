#include "interpreter/core/interpreter.h"
#include "exceptions/runtime/wrongFormOfMainException.h"


namespace interpreter {

	namespace core {

		CInterpreter::CInterpreter(ptr(ParserWrapper) parser, ptr(CBootstrapStage1) bootstrap, ptr(memory::memspace::CDescriptorTable) table)
			: m_parser(parser),
                          m_bootstrap(bootstrap),
                          m_descriptorTable(table) {
		}

		void CInterpreter::execProgram(ptr(ast_program) node) {
			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				exec(node->getNodeAt(i));
			}
                        ptr(mem_component) main = m_descriptorTable->getDescriptor(COMPO_MAIN_COMPONENT_NAME);
                        
                        
		}

		void CInterpreter::execDescriptor(ptr(ast_descriptor) node) {
                        std::string name = node->getNameSymbol()->getStringValue();
			if (m_descriptorTable->descriptorFound(name)) {
                            throw exceptions::semantic::CRedefinedDescriptorException(name);
			}
                        m_descriptorTable->addDescriptor(m_bootstrap->bootstrapDescriptorComponent(node));
		}

		void CInterpreter::exec(ptr(ast_node) node) {
			switch (node->getNodeType()) {
                            case type_node::PROGRAM : {
                                    execProgram(cast(ast_program)(node));
                                    break;
                            }
                            case type_node::DESCRIPTOR : {
                                    execDescriptor(cast(ast_descriptor)(node));
                                    break;
                            }
                            default : {
                                    throw exceptions::runtime::CUnknownAstNodeTypeException(typeName(node->getNodeType()));
                            }
			}
		}

		void CInterpreter::execService(const std::string& code) {
			std::stringstream input;
			std::string serviceCode = code;
			input.str(serviceCode);

			m_parser->parse(serviceCode);

			ptr(ast_compound) body = m_parser->getServiceBody();

			exec(body);
		}

		void CInterpreter::run(ptr(ast_program) ast) {
			exec(ast);
		}

	}

}