#pragma once

#include "compoNode.h"
#include "compoPort.h"

class CCompoProvision : public CCompoNode {
private:
            bool                            m_externally;
            std::vector<CCompoPort*>        m_ports;
            
public:
                                            CCompoProvision     (bool externally, std::vector<CCompoPort*> ports);
    virtual                                 ~CCompoProvision    ();
    virtual void                            print               (std::ostream& os) const;
            bool                            isExternal          ();
            std::vector<CCompoPort*> *      getPorts            ();
};