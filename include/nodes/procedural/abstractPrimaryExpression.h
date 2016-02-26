#pragma once

#include "nodes/node.h"
#include "nodes/procedural/abstractExpression.h"

namespace nodes {

    namespace procedural {

        /**
         * \class CAbstractPrimaryExpression
         * \brief Class for expression in parentheses.
         */
        class CAbstractPrimaryExpression : public virtual CAbstractExpression {        
        protected:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param type: type of node
                                                    * @param val: integer value
                                                    */
                                                    CAbstractPrimaryExpression             ();

                                                    /**
                                                    * Copy constructor
                                                    * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CAbstractPrimaryExpression             (const CAbstractPrimaryExpression& other);

                                                    /**
                                                    * Move constructor
                                                    * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CAbstractPrimaryExpression             (CAbstractPrimaryExpression&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CAbstractPrimaryExpression&                    operator =              (const CAbstractPrimaryExpression& other);

                                                    /**
                                                    * Move assignment operator
                                                    * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CAbstractPrimaryExpression&                    operator =              (CAbstractPrimaryExpression&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone                   () const;

        public:
                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CAbstractPrimaryExpression            ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print                   (std::ostream& outStr) const;
        };

    }
    
}