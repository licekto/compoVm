#include "interpreter/core/coreModules.h"
#include "exceptions/runtime/kernelModuleNotFoundException.h"
#include "parser/parserWrapper.h"

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
                }
                else {
                    throw exceptions::runtime::CKernelModuleNotFoundException(path);
                }
            }
            
            void CCoreModules::loadModules() {
                m_kernelComponentsCode[coreModuleType::COLLECTION_PORT] = readFile(KERNEL_COLLECTION_PORT_PATH);
                m_kernelComponentsCode[coreModuleType::COMPONENT] = readFile(KERNEL_COMPONENT_PATH);
                m_kernelComponentsCode[coreModuleType::CONNECTION_DESCRIPTION] = readFile(KERNEL_CONNECTION_DESCRIPTION_PATH);
                m_kernelComponentsCode[coreModuleType::DESCRIPTOR] = readFile(KERNEL_DESCRIPTOR_PATH);
                m_kernelComponentsCode[coreModuleType::PORT] = readFile(KERNEL_PORT_PATH);
                m_kernelComponentsCode[coreModuleType::PORT_DESCRIPTION] = readFile(KERNEL_PORT_DESCRIPTION_PATH);
                m_kernelComponentsCode[coreModuleType::SERVICE] = readFile(KERNEL_SERVICE_PATH);
                m_kernelComponentsCode[coreModuleType::SERVICE_SIGNATURE] = readFile(KERNEL_SERVICE_SIGNATURE_PATH);
            }

            std::string CCoreModules::getKernelModuleCode(coreModuleType module) const {
                return m_kernelComponentsCode.at(module);
            }
            
            ptr(ast_descriptor) CCoreModules::getKernelModuleAst(coreModuleType module) const {
                if (m_parser.use_count()) {
                    std::stringstream input;
                    input.str(m_kernelComponentsCode.at(module));
                    
                    m_parser->parse(input);
                    
                    return cast(ast_descriptor)(m_parser->getRootNode()->getNodeAt(0));
                }
                return nullptr;
            }

	}

}