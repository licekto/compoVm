#include "interpreter/memory/objects/primitives/primitiveService.h"

namespace interpreter {
    
    namespace memory {
        
        namespace objects {
            
            namespace primitives {

                CPrimitiveService::CPrimitiveService(const std::string& name,
                                                     std::vector<std::string> params,
                                                     ptr(objects::CComponent) context,
                                                     std::function<void()> callback)
                : CAbstractPrimitive(name, nullptr),
                  m_params(params),
                  m_context(context),
                  m_callback(callback) {
                }

                CPrimitiveService::~CPrimitiveService() {
                }

                void CPrimitiveService::operator()() {
                    m_callback();
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

                std::string CPrimitiveService::getName() const {
                    return m_name;
                }

                ptr(objects::CComponent) CPrimitiveService::getContext() {
                    return m_context;
                }

                void CPrimitiveService::setCallback(std::function<void()> callback) {
                    m_callback = callback;
                }

            }
            
        }
    }
}