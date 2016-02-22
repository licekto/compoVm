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
                                                CCompoProvision     ( visibilityType type = visibilityType::EXTERNAL,
                                                                      const std::vector<CCompoPort*>& ports = std::vector<CCompoPort*>(0));
                                                
                                                /**
                                                * Copy constructor
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoProvision     (const CCompoProvision& other);
                                                
                                                /**
                                                * Move constructor
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoProvision     (CCompoProvision&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoProvision&                operator=           (const CCompoProvision& other);
                                                
                                                /**
                                                * Move assignment operator
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoProvision&                operator=           (CCompoProvision&& other) noexcept;
                
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoProvision    ();
    };

}