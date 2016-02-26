#pragma once

#include "nodes/node.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

    namespace procedural {

        /**
         * \class CCompoAssignment
         * \brief Class for assignment representation.
         */
        class CAssignment : public CNode {
        private:
                    nodes::procedural::CSymbol                  * m_variable;     /**< Variable to assign to */
                    CNode                    * m_rValue;       /**< Right-hand side of assignment expression */

        public:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param variable: name of variable
                                                    * @param rval: right-hand side of assignment
                                                    */
                                                    CAssignment         (nodes::procedural::CSymbol * variable = nullptr, CNode * rVal = nullptr);

                                                    /**
                                                    * Copy constructor
                                                    * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CAssignment         (const CAssignment& other);

                                                    /**
                                                    * Move constructor
                                                    * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CAssignment         (CAssignment&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CAssignment&                    operator =          (const CAssignment& other);

                                                    /**
                                                    * Move assignment operator
                                                    * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CAssignment&                    operator =          (CAssignment&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone               () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CAssignment        ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print               (std::ostream& os) const;

                                                    /**
                                                    * Variable name getter
                                                    * @return Variable name
                                                    */
            nodes::procedural::CSymbol *                          getVariable         () const;

                                                    /**
                                                    * Right-hand side expression getter
                                                    * @return Expression node
                                                    */
            CNode *                            getRValue           () const;
        };

    }
    
}