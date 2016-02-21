#pragma once

#include "compoAbstractReqProv.h"

namespace compo {
    
    /**
     * \class CCompoProvision
     * \brief Class for Compo provision node representation.
     */
    class CCompoProvision : public CCompoAbstractReqProv {            
    public:
                                                /**
                                                * Parametric constructor with default value
                                                * @param type: Type of visibility
                                                * @param ports: Vector of ports
                                                */
                                                CCompoProvision     (   visibilityType type = visibilityType::EXTERNAL,
                                                                        const std::vector<CCompoPort*>& ports = std::vector<CCompoPort*>(0));
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoProvision    ();
    };

}