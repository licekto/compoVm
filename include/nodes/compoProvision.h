#pragma once

#include "nodeDefinitions.h"
#include "compoNode.h"
#include "compoPort.h"

class CCompoProvision : public CCompoNode {
private:
            bool                m_externally;
            PORT_VECTOR         m_ports;
            
public:
                                CCompoProvision     (bool externally, PORT_VECTOR ports);
    virtual                     ~CCompoProvision    ();
    virtual void                print               (std::ostream& os) const;
            bool                isExternal          ();
            PORT_VECTOR *       getPorts            ();
};