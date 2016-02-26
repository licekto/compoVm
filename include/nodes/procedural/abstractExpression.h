#pragma once

#include "nodes/node.h"

namespace nodes {

    /**
     *  \addtogroup procedural
     *  @{
     */

    /**
     * procedural Namespace to uniquely identify compo AST nodes.
     */
    namespace procedural {

        /**
         * \class CAbstractExpression
         * \brief Class for abstract expression representation.
         */
        class CAbstractExpression : public virtual CNode {        
        protected:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param type: type of node
                                                    * @param val: integer value
                                                    */
                                                    CAbstractExpression             ();

                                                    /**
                                                    * Copy constructor
                                                    * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CAbstractExpression             (const CAbstractExpression& other);

                                                    /**
                                                    * Move constructor
                                                    * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CAbstractExpression             (CAbstractExpression&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CAbstractExpression&                    operator =              (const CAbstractExpression& other);

                                                    /**
                                                    * Move assignment operator
                                                    * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CAbstractExpression&                    operator =              (CAbstractExpression&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone                   () const;

        public:
                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CAbstractExpression            ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print                   (std::ostream& outStr) const;
        };

    }
    
}