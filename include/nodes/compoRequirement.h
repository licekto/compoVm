#pragma once

#include "compoAbstractReqProv.h"

class CCompoRequirement : public CCompoAbstractReqProv {            
public:
                                            CCompoRequirement     ( visibilityType type = visibilityType::EXTERNAL,
                                                                    std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0));
    virtual                                 ~CCompoRequirement    ();
};