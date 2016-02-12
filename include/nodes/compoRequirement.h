#pragma once

#include "compoAbstractReqProv.h"

class CCompoRequirement : public CCompoAbstractReqProv {            
public:
                                            CCompoRequirement     (intExtType type, std::vector<CCompoPort*> ports);
    virtual                                 ~CCompoRequirement    ();
};