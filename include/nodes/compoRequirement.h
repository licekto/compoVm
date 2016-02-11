#pragma once

#include "compoNode.h"
#include "compoPort.h"

class CCompoRequirement : public CCompoNode {
private:
            bool                        m_externally;
            std::vector<CCompoPort*>    m_ports;
            
public:
                                        CCompoRequirement   (bool m_externally, std::vector<CCompoPort*> ports);
    virtual                             ~CCompoRequirement  ();
    virtual void                        print               (std::ostream& os) const;
            bool                        isExternal          ();
            std::vector<CCompoPort*> *  getPorts            ();
};