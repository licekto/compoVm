#pragma once

#include "compoAbstractService.h"

class CCompoService : public CCompoAbstractService {
private:
                std::vector<CCompoNode*>    m_temporaries;
public:

                                        CCompoService           (   CCompoSymbol* name = nullptr,
                                                                    std::vector<CCompoSymbol*> params = std::vector<CCompoSymbol*>(0),
                                                                    std::vector<CCompoNode*> body = std::vector<CCompoNode*>(0),
                                                                    std::vector<CCompoNode*> temporaries = std::vector<CCompoNode*>(0)  );
    virtual                             ~CCompoService          ();
            std::vector<CCompoNode*> *  getTemporaries          () const;
};