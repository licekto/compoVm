#include "interpreter/core/coreModules.h"

namespace interpreter {

	namespace core {

		CCoreModules::CCoreModules(std::shared_ptr<ParserWrapper> parser)
			: m_parser(parser) {
		}

		std::string CCoreModules::readFile(const std::string& path) const {
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

		void CCoreModules::loadDescriptor(const std::string& path) {
			m_parser->clearAll();
			m_parser->parse(readFile(path));

			m_coreDescriptors.push_back(cast(ast_descriptor)(m_parser->getRootNode()->getNodeAt(0)));
		}

		ptr(ast_descriptor) CCoreModules::getCoreDescriptor(const std::string& module) const {
			auto it = std::find_if(m_coreDescriptors.begin(), m_coreDescriptors.end(), [&module] (ptr(ast_descriptor) descriptor) {
				return descriptor->getNameSymbol()->getStringValue() == module;
			});

			if (it == m_coreDescriptors.end()) {
                                // throw
				return nullptr;
			}
			return *it;
		}

		void CCoreModules::loadCoreModules() {
			loadDescriptor(KERNEL_COLLECTION_PORT_PATH);
			loadDescriptor(KERNEL_COMPONENT_PATH);
			loadDescriptor(KERNEL_CONNECTION_DESCRIPTION_PATH);
			loadDescriptor(KERNEL_DESCRIPTOR_PATH);
			loadDescriptor(KERNEL_INTERFACE_PATH);
			loadDescriptor(KERNEL_PORT_PATH);
			loadDescriptor(KERNEL_PORT_DESCRIPTION_PATH);
			loadDescriptor(KERNEL_SERVICE_PATH);
			loadDescriptor(KERNEL_SERVICE_SIGNATURE_PATH);
                        loadDescriptor(KERNEL_SERVICE_INVOCATION_PATH);
		}

		ptr(ast_descriptor) CCoreModules::getCoreDescriptorAt(size_t i) const {
			if (i < m_coreDescriptors.size()) {
				return m_coreDescriptors.at(i);
			}
			return nullptr;
		}

		size_t CCoreModules::getCoreDescriptorsSize() const {
			return m_coreDescriptors.size();
		}

	}

}