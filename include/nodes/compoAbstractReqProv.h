#pragma once

#include "compoNode.h"
#include "compoPort.h"
#include "visibilityType.h"

class CCompoAbstractReqProv : public virtual CCompoNode {
protected:
            visibilityType                      m_intExtType;
            std::vector<CCompoPort*>        m_ports;
            
                                            CCompoAbstractReqProv   (visibilityType type, std::vector<CCompoPort*> ports);
                                            
public:
    virtual                                 ~CCompoAbstractReqProv  ();
    virtual void                            print                   (std::ostream& os) const;
            visibilityType                  getVisibilityType       ();
            std::vector<CCompoPort*> *      getPorts                () const;
};