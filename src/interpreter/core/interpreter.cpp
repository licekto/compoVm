#include "interpreter/core/interpreter.h"
#include "interpreter/memory/objects/stringComponent.h"
#include "interpreter/memory/objects/primitivePort.h"

namespace interpreter {

	namespace core {

		CInterpreter::CInterpreter(ptr(ast::semantic::CGlobalDescriptorTable) table,
		                           ptr(memory::manager::CMemoryManager) manager,
                                           ptr(CCoreModules) modules)
			: m_ast(nullptr),
			  m_descriptorTable(table),
			  m_memory(manager),
                          m_coreModules(modules) {
		}

		void CInterpreter::checkMainContainer() const {
			if (!m_descriptorTable->symbolFound(COMPO_MAIN_COMPONENT_NAME)) {
				throw exceptions::runtime::CMainComponentMissingException();
			}

			ptr(ast_descriptor) container = cast(ast_descriptor)(m_descriptorTable->getSymbol(COMPO_MAIN_COMPONENT_NAME));

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
                    if (!m_descriptorTable->symbolFound(node->getNameSymbol()->getStringValue())) {
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
                            m_descriptorTable->addSymbol(m_coreModules->getCoreDescriptorAt(i));
                        }
                    }
                }
                
		void CInterpreter::run(ptr(ast_program) ast) {
                        checkMainContainer();
                        loadCoreToDescriptorTable();
                        
                        exec(ast);
		}

	}

}