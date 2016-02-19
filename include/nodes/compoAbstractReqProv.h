#pragma once

#include "compoNode.h"
#include "compoPort.h"
#include "visibilityType.h"

class CCompoAbstractReqProv : public virtual CCompoNode {
protected:
            visibilityType                      m_intExtType;
            std::vector<CCompoPort*>        m_ports;
            
                                            CCompoAbstractReqProv   (   visibilityType type = visibilityType::EXTERNAL,
                                                                        std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0));
                                            
public:
    virtual                                 ~CCompoAbstractReqProv  ();
    virtual void                            print                   (std::ostream& os) const;
            visibilityType                  getVisibilityType       ();
            std::vector<CCompoPort*> *      getPorts                () const;
};