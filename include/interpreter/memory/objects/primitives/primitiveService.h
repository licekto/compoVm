#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {
    
    namespace memory {
        
        namespace objects {
            
            namespace primitives {
        
                class CPrimitiveService : public CAbstractPrimitive {

                    std::string m_name;
                    
                    std::vector<std::string> m_params;

                    ptr(objects::CComponent) m_context;
                    
                    std::function<void()> m_callback;

                public:

                    CPrimitiveService(const std::string& name = "",
                                      std::vector<std::string> params = std::vector<std::string>(0),
                                      ptr(CComponent) context = nullptr,
                                      std::function<void()> callback = std::function<void()>());

                    virtual ~CPrimitiveService();
                    
                    void operator()();
                    
                    size_t getParamsCount() const;

                    std::string getParamName(size_t index) const;

                    void setParam(std::string param);

                    std::string getName() const;
                    
                    ptr(objects::CComponent) getContext();
                    
                    void setCallback(std::function<void()> callback);
                };
            
            }
        }
    }
}