#pragma once

#include "nodeDefinitions.h"
#include "compoNode.h"
#include "compoSymbol.h"


class CCompoDescriptor : public CCompoNode {
private:
            CCompoSymbol      * m_name;
            CCompoSymbol      * m_extends;
            NODE_VECTOR         m_body;
            
public:
                                CCompoDescriptor    (CCompoSymbol *name, CCompoSymbol *extends, NODE_VECTOR body);
    virtual                     ~CCompoDescriptor   ();
    virtual void                print               (std::ostream& os) const;
            CCompoSymbol *      getName             () const;
            void                setExtends          (CCompoSymbol * extends);
            CCompoSymbol *      getExtends          () const;
};