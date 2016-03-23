#include "interpreter/core/kernelLoader.h"
#include "exceptions/runtime/kernelModuleNotFoundException.h"
#include "parser/parserWrapper.h"

namespace interpreter {

	namespace core {
            
            CKernelLoader::CKernelLoader(std::shared_ptr<ParserWrapper> parser)
            : m_parser(parser) {
            }
            
            std::string CKernelLoader::readFile(std::string path) const {
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
            
            void CKernelLoader::loadModules() {
                m_kernelComponentsCode[kernelModules::COLLECTION_PORT] = readFile(KERNEL_COLLECTION_PORT_PATH);
                m_kernelComponentsCode[kernelModules::COMPONENT] = readFile(KERNEL_COMPONENT_PATH);
                m_kernelComponentsCode[kernelModules::CONNECTION_DESCRIPTION] = readFile(KERNEL_CONNECTION_DESCRIPTION_PATH);
                m_kernelComponentsCode[kernelModules::DESCRIPTOR] = readFile(KERNEL_DESCRIPTOR_PATH);
                m_kernelComponentsCode[kernelModules::PORT] = readFile(KERNEL_PORT_PATH);
                m_kernelComponentsCode[kernelModules::PORT_DESCRIPTION] = readFile(KERNEL_PORT_DESCRIPTION_PATH);
                m_kernelComponentsCode[kernelModules::SERVICE] = readFile(KERNEL_SERVICE_PATH);
                m_kernelComponentsCode[kernelModules::SERVICE_SIGNATURE] = readFile(KERNEL_SERVICE_SIGNATURE_PATH);
            }

            std::string CKernelLoader::getKernelModuleCode(kernelModules module) const {
                return m_kernelComponentsCode.at(module);
            }
            
            ptr(ast_descriptor) CKernelLoader::getKernelModuleAst(kernelModules module) const {
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