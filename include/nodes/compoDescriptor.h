#pragma once

#include "compoNode.h"
#include "compoSymbol.h"


class CCompoDescriptor : public CCompoNode {
private:
            CCompoSymbol              * m_name;
            CCompoSymbol              * m_extends;
            std::vector<CCompoNode*>    m_body;
            
public:
                                CCompoDescriptor    (CCompoSymbol *name, CCompoSymbol *extends, std::vector<CCompoNode*> body);
    virtual                     ~CCompoDescriptor   ();
    virtual void                print               (std::ostream& os) const;
            CCompoSymbol *      getName             () const;
            void                setExtends          (CCompoSymbol * extends);
            CCompoSymbol *      getExtends          () const;
};