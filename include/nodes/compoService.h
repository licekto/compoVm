#pragma once

#include "compoAbstractService.h"

class CCompoService : public CCompoAbstractService {
public:

                CCompoService   (CCompoSymbol *name, std::vector<CCompoSymbol*> params, std::vector<CCompoNode*> body);
    virtual     ~CCompoService  ();
};