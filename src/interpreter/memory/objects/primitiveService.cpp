#include "interpreter/memory/objects/primitiveService.h"

namespace interpreter {
    
    namespace memory {
        
        namespace objects {
            
            CPrimitiveService::CPrimitiveService(ptr(core::native::CNativeCall) call, const std::string& selector, std::vector<std::string> params)
            : m_call(call),
              m_selector(selector),
              m_params(params) {
            }

            void CPrimitiveService::setSelector(std::string selector) {
                m_selector = selector;
            }

            std::string CPrimitiveService::getSelector() const {
                return m_selector;
            }

            size_t CPrimitiveService::getParamsCount() const {
                return m_params.size();
            }

            std::string CPrimitiveService::getParamName(size_t index) const {
                if (index < m_params.size()) {
                    return m_params.at(index);
                }
                //throw exception
                return "";
            }

            void CPrimitiveService::setParam(std::string param) {
                m_params.push_back(param);
            }

            void CPrimitiveService::setCall(std::shared_ptr<core::native::CNativeCall> call) {
                m_call = call;
            }

            std::shared_ptr<core::native::CNativeCall> CPrimitiveService::getCall() const {
                return m_call;
            }
            
        }
    }
}