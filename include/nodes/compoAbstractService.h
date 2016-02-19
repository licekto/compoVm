#pragma once

#include "compoNode.h"
#include "compoSymbol.h"


class CCompoAbstractService : public virtual CCompoNode {
protected:
            CCompoSymbol              * m_name;
            std::vector<CCompoSymbol*>  m_params;
            std::vector<CCompoNode*>    m_body;
            
public:
                                        CCompoAbstractService   (   CCompoSymbol *name = nullptr,
                                                                    std::vector<CCompoSymbol*> params = std::vector<CCompoSymbol*>(0),
                                                                    std::vector<CCompoNode*> body = std::vector<CCompoNode*>(0));
    virtual                             ~CCompoAbstractService  ();
    virtual void                        print                   (std::ostream& os) const;
            CCompoSymbol *              getName                 () const;
            std::vector<CCompoNode*> *  getBody                 () const;
            void                        setBody                 (std::vector<CCompoNode*> body);
            std::vector<CCompoSymbol*> *getParams               () const;
            void                        setParam                (CCompoSymbol *param);
};