#pragma once

#include "nodes/compoNode.h"
#include "nodes/proceduralNodes/compoSymbol.h"

namespace compo {
    
    /**
     * \class CCompoAssignment
     * \brief Class for assignment representation.
     */
    class CCompoAssignment : public CCompoNode {
    private:
                CCompoSymbol                  * m_variable;     /**< Variable to assign to */
                CCompoNode                    * m_rValue;       /**< Right-hand side of assignment expression */

    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param variable: name of variable
                                                * @param rval: right-hand side of assignment
                                                */
                                                CCompoAssignment        (CCompoSymbol * variable = nullptr, CCompoNode * rVal = nullptr);
                                                                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoAssignment        (const CCompoAssignment& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoAssignment        (CCompoAssignment&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoAssignment&               operator =              (const CCompoAssignment& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoAssignment&               operator =              (CCompoAssignment&& other) noexcept;
    
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                       () const;
                                                
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoAssignment       ();
        
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print                   (std::ostream& os) const;
        
                                                /**
                                                * Variable name getter
                                                * @return Variable name
                                                */
        CCompoSymbol *                          getVariable             () const;
        
                                                /**
                                                * Right-hand side expression getter
                                                * @return Expression node
                                                */
        CCompoNode *                            getRValue               () const;
    };

}