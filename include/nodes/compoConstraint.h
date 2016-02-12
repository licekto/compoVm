#pragma once

#include "compoAbstractService.h"

class CCompoConstraint : public CCompoAbstractService {
public:

                CCompoConstraint    (CCompoSymbol *name, std::vector<CCompoSymbol*> params, std::vector<CCompoNode*> body);
    virtual     ~CCompoConstraint   ();
};