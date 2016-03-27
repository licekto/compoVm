#pragma once

namespace interpreter {
    
    namespace core {
        
        namespace native {
        
            class CNativeCall {
            public:
                virtual void operator() () = 0;
            };
        
        }
        
    }
}