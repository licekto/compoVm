#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/core/native/nativeCall.h"

namespace interpreter {
    
    namespace memory {
        
        namespace objects {
        
            class CPrimitiveService : public CComponent {
                
                ptr(core::native::CNativeCall) m_call;
                
                std::string m_selector;
                
                std::vector<std::string> m_params;
                
            public:

                CPrimitiveService(ptr(core::native::CNativeCall) call = nullptr, const std::string& selector = "", std::vector<std::string> params = std::vector<std::string>(0));
                
                std::string getSelector() const;
                
                void setSelector(std::string selector);
                
                size_t getParamsCount() const;
                
                std::string getParamName(size_t index) const;
                
                void setParam(std::string param);
                
                void setCall(ptr(core::native::CNativeCall) call);
                
                ptr(core::native::CNativeCall) getCall() const;
                
                void setDefaultPort(ptr(CComponent) defaultPort) = delete;

                void setSelfPort(ptr(CComponent) selfPort) = delete;

                void setSuperPort(ptr(CComponent) superPort) = delete;

                void addPort(ptr(CComponent) port) = delete;

                void addService(ptr(CComponent) service) = delete;
            };
        }
    }
}