#pragma once

#include "nodes/compoNode.h"
#include "types.h"

namespace compo {

    /**
     * \class CCompoIntegerLiteral
     * \brief Class for integer literal representation.
     * 
     * Class contains positive or negative 4B integer value.
     */
    class CCompoConstant : public CCompoNode {
    private:
                i32                             m_intValue;         /**< Integer 4B value */
        
    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param type: type of node
                                                * @param val: integer value
                                                */
                                                CCompoConstant      (i32 val = 0);
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoConstant      (const CCompoConstant& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoConstant      (CCompoConstant&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoConstant&                 operator =          (const CCompoConstant& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoConstant&                 operator =          (CCompoConstant&& other) noexcept;

                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone               () const;
        
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoConstant     ();
        
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print               (std::ostream& outStr) const;
        
                                                /**
                                                 * Integer value getter
                                                 * @return integer value
                                                 */
                i32                             getValue            () const;
    };

}