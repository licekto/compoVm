#pragma once

#include "nodes/compoNode.h"

namespace compo {

    /**
     * \class CCompoParens
     * \brief Class for expression in parentheses.
     */
    class CCompoExpression : public CCompoNode {        
    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param type: type of node
                                                * @param val: integer value
                                                */
                                                CCompoExpression        ();
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoExpression        (const CCompoExpression& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoExpression        (CCompoExpression&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoExpression&               operator =              (const CCompoExpression& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoExpression&               operator =              (CCompoParens&& other) noexcept;

                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                   () const;
        
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoExpression       ();
        
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
                CCompoNode *                    getExpression       () const;
    };

}