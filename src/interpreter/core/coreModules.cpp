#include "interpreter/core/coreModules.h"

namespace interpreter {

	namespace core {

		CCoreModules::CCoreModules(std::shared_ptr<ParserWrapper> parser)
			: m_parser(parser) {
		}

		std::string CCoreModules::readFile(std::string path) const {
			std::string line, content;

			std::ifstream file(path);

			if (file.is_open()) {
				while (std::getline(file, line)) {
					content += line;
					content.push_back('\n');
				}
				file.close();
				return content;
			} else {
				throw exceptions::runtime::CCoreModuleNotFoundException(path);
			}
		}

                void CCoreModules::getModule(coreModuleType module, std::string path) {
                        m_parser->parse(readFile(path));
                        
                        m_kernelComponents[module] = cast(ast_descriptor)(m_parser->getRootNode()->getNodeAt(0));
                        m_parser->clearAll();
                }
                
		void CCoreModules::loadModules() {
                        getModule(coreModuleType::COLLECTION_PORT, KERNEL_COLLECTION_PORT_PATH);
                        getModule(coreModuleType::COMPONENT, KERNEL_COMPONENT_PATH);
                        getModule(coreModuleType::CONNECTION_DESCRIPTION, KERNEL_CONNECTION_DESCRIPTION_PATH);
                        getModule(coreModuleType::DESCRIPTOR, KERNEL_DESCRIPTOR_PATH);
                        getModule(coreModuleType::PORT, KERNEL_PORT_PATH);
                        getModule(coreModuleType::PORT_DESCRIPTION, KERNEL_PORT_DESCRIPTION_PATH);
                        getModule(coreModuleType::SERVICE, KERNEL_SERVICE_PATH);
                        getModule(coreModuleType::SERVICE_SIGNATURE, KERNEL_SERVICE_SIGNATURE_PATH);
		}

		ptr(ast_descriptor) CCoreModules::getKernelModule(coreModuleType module) const {
			return m_kernelComponents.at(module);
		}
                
                void CCoreModules::bootstrap() {
                    loadModules();
                    
                    ptr(ast_descriptor) component = getKernelModule(core::coreModuleType::COMPONENT);
                    ptr(ast_descriptor) descriptor = getKernelModule(core::coreModuleType::DESCRIPTOR);
                    
                    
                }

	}

}