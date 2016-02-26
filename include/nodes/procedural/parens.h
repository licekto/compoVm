#pragma once

#include "nodes/node.h"
#include "abstractPrimaryExpression.h"


namespace nodes {

    namespace procedural {

        /**
         * \class CParens
         * \brief Class for expression in parentheses.
         */
        class CParens : public CAbstractPrimaryExpression {
        private:
                    CNode                       * m_expression;         /**< Expression in parentheses */

        public:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param type: type of node
                                                    * @param val: integer value
                                                    */
                                                    CParens         (CNode *expr = nullptr);

                                                    /**
                                                    * Copy constructor
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CParens         (const CParens& other);

                                                    /**
                                                    * Move constructor
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CParens         (CParens&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CParens&                        operator =      (const CParens& other);

                                                    /**
                                                    * Move assignment operator
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CParens&                        operator =      (CParens&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone           () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CParens        ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print           (std::ostream& outStr) const;

                                                    /**
                                                     * Expression getter
                                                     * @return nodes::CNode pointer
                                                     */
                    CNode *                    getExpression   () const;
        };

    }
    
}