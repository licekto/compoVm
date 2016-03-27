#pragma once

#include "nativeCall.h"

namespace interpreter {
    
    namespace core {
        
        namespace native {
        
            class CNewCall : public CNativeCall {
            public:
                virtual void operator ()();
            };
        
        }
        
    }
}