#pragma once

#include "compoAbstractServConstr.h"

namespace compo {
    
    /**
     * \class CCompoConstraint
     * \brief Class for Compo constraint representation.
     */
    class CCompoConstraint : public CCompoAbstractServConstr {
    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param name: Name of constraint
                                                * @param params: Vector of parameters
                                                * @param body: Vector of body expressions
                                                */
                                                CCompoConstraint    ( CCompoSymbol *name = nullptr,
                                                                      const std::vector<CCompoSymbol*>& params = std::vector<CCompoSymbol*>(0),
                                                                      const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0));
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoConstraint    (const CCompoConstraint& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoConstraint    (CCompoConstraint&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoConstraint&               operator =          (const CCompoConstraint& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoConstraint&               operator =          (CCompoConstraint&& other) noexcept;
    
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone               () const;
        
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoConstraint   ();
    };

}