#pragma once

#include "compoNode.h"
#include "compoSymbol.h"


class CCompoService : public CCompoNode {
private:
            CCompoSymbol              * m_name;
            std::vector<CCompoSymbol*>  m_params;
            std::vector<CCompoNode*>    m_body;
            
public:
                                        CCompoService       (CCompoSymbol *name, std::vector<CCompoSymbol*> params, std::vector<CCompoNode*> body);
    virtual                             ~CCompoService      ();
    virtual void                        print               (std::ostream& os) const;
            CCompoSymbol *              getName             () const;
            std::vector<CCompoNode*> *  getBody             ();
            void                        setBody             (std::vector<CCompoNode*> body);
            std::vector<CCompoSymbol*> *getParams           ();
            void                        setParam            (CCompoSymbol *param);
};