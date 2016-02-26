#pragma once

#include "nodes/node.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

    namespace procedural {

        /**
         * \class CBinaryExpression
         * \brief Class for assignment representation.
         */
        class CBinaryExpression : public virtual CAbstractExpression {
        private:
                    types::operatorType             m_operator;         /**< Operator */
                    CAbstractPrimaryExpression    * m_operand1;         /**< First operand */
                    CAbstractPrimaryExpression    * m_operand2;         /**< Second operand */

        public:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param variable: name of variable
                                                    * @param rval: right-hand side of assignment
                                                    */
                                                    CBinaryExpression         ( types::operatorType type = types::operatorType::PLUS,
                                                                                CAbstractPrimaryExpression * op1 = nullptr,
                                                                                CAbstractPrimaryExpression * op2 = nullptr);

                                                    /**
                                                    * Copy constructor
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CBinaryExpression         (const CBinaryExpression& other);

                                                    /**
                                                    * Move constructor
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CBinaryExpression         (CBinaryExpression&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CBinaryExpression&                    operator =          (const CBinaryExpression& other);

                                                    /**
                                                    * Move assignment operator
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CBinaryExpression&                    operator =          (CBinaryExpression&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone               () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CBinaryExpression        ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print               (std::ostream& os) const;

                                                    /**
                                                    * Operator getter
                                                    * @return Operator type
                                                    */
            types::operatorType                     getOperator         () const;
            
                                                    /**
                                                    * First operand getter
                                                    * @return Operand expression pointer
                                                    */
            CAbstractPrimaryExpression *            getOperand1         () const;

                                                    /**
                                                    * Second operand getter
                                                    * @return Operand expression pointer
                                                    */
            CAbstractPrimaryExpression *            getOperand2         () const;
        };

    }
    
}