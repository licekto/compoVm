#pragma once

#include "compoNode.h"
#include "compoSymbol.h"

class CCompoPort : public virtual CCompoNode {
protected:
            CCompoSymbol      * m_name;
            bool                m_atomic;
            
public:
                                CCompoPort          (CCompoSymbol *name, bool atomic);
    virtual                     ~CCompoPort         ();
    virtual void                print               (std::ostream& os) const;
            CCompoSymbol *      getName             () const;
};