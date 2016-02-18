#pragma once

#include "compoPort.h"

class CCompoInjectedPort : public CCompoPort {
private:
                        CCompoSymbol          * m_injectedWith;
        
public:
                        CCompoInjectedPort      (CCompoSymbol *name, bool atomic, CCompoSymbol * injectedWith);
    virtual             ~CCompoInjectedPort     ();
    virtual void        print                   (std::ostream& os) const;
};