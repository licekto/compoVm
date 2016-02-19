#pragma once

#include "compoAbstractService.h"

class CCompoConstraint : public CCompoAbstractService {
public:

                CCompoConstraint    (   CCompoSymbol *name = nullptr,
                                        std::vector<CCompoSymbol*> params = std::vector<CCompoSymbol*>(0),
                                        std::vector<CCompoNode*> body = std::vector<CCompoNode*>(0));
    virtual     ~CCompoConstraint   ();
};