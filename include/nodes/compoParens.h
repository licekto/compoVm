#pragma once

#include "compoNode.h"
#include "types.h"

namespace compo {

    /**
     * \class CCompoParens
     * \brief Class for expression in parentheses.
     */
    class CCompoParens : public CCompoNode {
    private:
                CCompoNode                    * m_expression;         /**< Expression in parentheses */
        
    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param type: type of node
                                                * @param val: integer value
                                                */
                                                CCompoParens        (CCompoNode *expr = nullptr);
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoParens        (const CCompoParens& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoParens        (CCompoParens&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoParens&                   operator =          (const CCompoParens& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoParens&                   operator =          (CCompoParens&& other) noexcept;

                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone               () const;
        
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoParens       ();
        
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