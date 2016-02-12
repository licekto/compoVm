#pragma once

#include "compoAbstractReqProv.h"

class CCompoProvision : public CCompoAbstractReqProv {            
public:
                                            CCompoProvision     (intExtType type, std::vector<CCompoPort*> ports);
    virtual                                 ~CCompoProvision    ();
};