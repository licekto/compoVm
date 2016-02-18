#pragma once

#include "compoAbstractReqProv.h"

class CCompoRequirement : public CCompoAbstractReqProv {            
public:
                                            CCompoRequirement     (visibilityType type, std::vector<CCompoPort*> ports);
    virtual                                 ~CCompoRequirement    ();
};