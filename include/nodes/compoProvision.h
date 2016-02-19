#pragma once

#include "compoAbstractReqProv.h"

class CCompoProvision : public CCompoAbstractReqProv {            
public:
                                            CCompoProvision     (   visibilityType type = visibilityType::EXTERNAL,
                                                                    std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0));
    virtual                                 ~CCompoProvision    ();
};