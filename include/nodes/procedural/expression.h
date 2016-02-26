#pragma once

#include "nodes/node.h"

namespace nodes {

    namespace procedural {

        /**
         * \class CCompoParens
         * \brief Class for expression in parentheses.
         */
        class CExpression : public CCompoNode {        
        public:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param type: type of node
                                                    * @param val: integer value
                                                    */
                                                    CExpression             ();

                                                    /**
                                                    * Copy constructor
                                                    * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CExpression             (const CExpression& other);

                                                    /**
                                                    * Move constructor
                                                    * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CExpression             (CExpression&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CExpression&                    operator =              (const CExpression& other);

                                                    /**
                                                    * Move assignment operator
                                                    * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CExpression&                    operator =              (CExpression&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CCompoNode *                    clone                   () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CExpression            ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print                   (std::ostream& outStr) const;

                                                    /**
                                                     * Integer value getter
                                                     * @return integer value
                                                     */
                    CCompoNode *                    getExpression           () const;
        };

    }
    
}