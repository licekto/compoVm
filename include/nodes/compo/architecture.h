#pragma once

#include "nodes/node.h"

namespace nodes {

    namespace compo {

        /**
         * \class CArchitecture
         * \brief Class for Compo architecture representation.
         */
        class CArchitecture : public CNode {
        private:

        public:
                                                    /**
                                                    * Parametric constructor
                                                    */
                                                    CArchitecture      ();

                                                    /**
                                                    * Copy constructor
                                                    * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CArchitecture      (const CArchitecture& other);

                                                    /**
                                                    * Move constructor
                                                    * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CArchitecture      (CArchitecture&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CArchitecture&             operator =              (const CArchitecture& other);

                                                    /**
                                                    * Move assignment operator
                                                    * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CArchitecture&             operator =              (CArchitecture&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone                   () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CArchitecture     ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print               (std::ostream& os) const;
        };

    }
    
}