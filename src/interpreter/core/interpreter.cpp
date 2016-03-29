#include "interpreter/core/interpreter.h"
#include "interpreter/memory/objects/stringComponent.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"

namespace interpreter {

	namespace core {

		CInterpreter::CInterpreter(ptr(ParserWrapper) parser,
		                           ptr(CCoreModules) modules)
			: m_ast(nullptr),
			  m_parser(parser),
			  m_coreModules(modules) {
		}

		void CInterpreter::checkMainContainer() const {
			if (!m_parser->getDescriptorTable()->symbolFound(COMPO_MAIN_COMPONENT_NAME)) {
				throw exceptions::runtime::CMainComponentMissingException();
			}

			ptr(ast_descriptor) container = cast(ast_descriptor)(m_parser->getDescriptorTable()->getSymbol(COMPO_MAIN_COMPONENT_NAME));

			if (!container->getServiceByName(COMPO_MAIN_SERVICE_NAME).use_count()) {
				throw exceptions::runtime::CMainServiceMissingException();
			}
		}

		void CInterpreter::execProgram(ptr(ast_program) node) {
			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				exec(node->getNodeAt(i));
			}
		}

		void CInterpreter::execDescriptor(ptr(ast_descriptor) node) {
			if (!m_parser->getDescriptorTable()->symbolFound(node->getNameSymbol()->getStringValue())) {
				// throw exception
			}
			// create descriptor component -> instance of Descriptor
		}

		void CInterpreter::exec(ptr(ast_node) node) {
			switch (node->getNodeType()) {
			case ast_nodetype::PROGRAM : {
				execProgram(cast(ast_program)(node));
				break;
			}
			case ast_nodetype::DESCRIPTOR : {
				execDescriptor(cast(ast_descriptor)(node));
				break;
			}
			default : {
				// throw exception
			}
			}
		}

		void CInterpreter::loadCoreToDescriptorTable() {
			if (m_coreModules.use_count()) {
				m_coreModules->loadCoreModules();

				for (size_t i = 0; i < m_coreModules->getCoreDescriptorsSize(); ++i) {
					m_parser->getDescriptorTable()->addSymbol(m_coreModules->getCoreDescriptorAt(i));
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
			checkMainContainer();
			loadCoreToDescriptorTable();

			exec(ast);
		}

	}

}