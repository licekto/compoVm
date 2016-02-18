#pragma once

#include "compoAbstractReqProv.h"

class CCompoProvision : public CCompoAbstractReqProv {            
public:
                                            CCompoProvision     (visibilityType type, std::vector<CCompoPort*> ports);
    virtual                                 ~CCompoProvision    ();
};