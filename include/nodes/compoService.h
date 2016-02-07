#pragma once

#include "nodeDefinitions.h"
#include "compoNode.h"
#include "compoSymbol.h"


class CCompoService : public CCompoNode {
private:
            CCompoSymbol      * m_name;
            SYMBOL_VECTOR       m_params;
            NODE_VECTOR         m_body;
            
public:
                                CCompoService       (CCompoSymbol *name, SYMBOL_VECTOR params, NODE_VECTOR body);
    virtual                     ~CCompoService      ();
    virtual void                print               (std::ostream& os) const;
            CCompoSymbol *      getName             () const;
            NODE_VECTOR *       getBody             ();
            void                setBody             (NODE_VECTOR body);
            SYMBOL_VECTOR *     getParams           ();
            void                setParam            (CCompoSymbol *param);
};