#pragma once

#include "compoAbstractReqProv.h"

namespace compo {
    
    /**
     * \class CCompoRequirement
     * \brief Class for Compo requirement node representation.
     */
    class CCompoRequirement : public CCompoAbstractReqProv {            
    public:
                                                /**
                                                * Parametric constructor with default value
                                                * @param type: Type of visibility
                                                * @param ports: Vector of ports
                                                */
                                                CCompoRequirement       ( visibilityType type = visibilityType::EXTERNAL,
                                                                          const std::vector<CCompoPort*>& ports = std::vector<CCompoPort*>(0) );
                                                /**
                                                * Copy constructor
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoRequirement       (const CCompoRequirement& other);
                                                
                                                /**
                                                * Move constructor
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoRequirement       (CCompoRequirement&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoRequirement&              operator=               (const CCompoRequirement& other);
                                                
                                                /**
                                                * Move assignment operator
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoRequirement&              operator=               (CCompoRequirement&& other) noexcept;
                                                
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoRequirement      ();
    };

}