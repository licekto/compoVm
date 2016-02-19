#pragma once

#include "compoNode.h"
#include "compoSymbol.h"

class CCompoAssignment : public CCompoNode {
private:
    CCompoSymbol      * m_variable;
    CCompoNode        * m_rValue;
    
public:
                                        CCompoAssignment        (CCompoSymbol * variable = nullptr, CCompoNode * rVal = nullptr);
    virtual                             ~CCompoAssignment       ();
    virtual void                        print                   (std::ostream& os) const;
    CCompoSymbol *                      getVariable             () const;
    CCompoNode *                        getRValue               () const;
};