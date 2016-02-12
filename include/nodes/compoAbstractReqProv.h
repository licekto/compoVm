#pragma once

#include "compoNode.h"
#include "compoPort.h"
#include "intExtType.h"

class CCompoAbstractReqProv : public virtual CCompoNode {
protected:
            intExtType                      m_intExtType;
            std::vector<CCompoPort*>        m_ports;
            
                                            CCompoAbstractReqProv   (intExtType type, std::vector<CCompoPort*> ports);
                                            
public:
    virtual                                 ~CCompoAbstractReqProv  ();
    virtual void                            print                   (std::ostream& os) const;
            intExtType                      getType                 ();
            std::vector<CCompoPort*> *      getPorts                ();
};