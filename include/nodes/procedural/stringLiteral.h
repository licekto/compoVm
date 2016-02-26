#pragma once

#include "nodes/node.h"

namespace nodes {

    namespace procedural {

        /**
         * \class CStringLiteral
         * \brief Class for integer literal representation.
         * 
         * Class contains positive or negative 4B integer value.
         */
        class CStringLiteral : public CNode {
        private:
                    std::string                     m_stringValue;         /**< String value */

        public:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param type: type of node
                                                    * @param val: integer value
                                                    */
                                                    CStringLiteral         (const std::string& val = "");

                                                    /**
                                                    * Copy constructor
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CStringLiteral         (const CStringLiteral& other);

                                                    /**
                                                    * Move constructor
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CStringLiteral         (CStringLiteral&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CStringLiteral&            operator =                  (const CStringLiteral& other);

                                                    /**
                                                    * Move assignment operator
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CStringLiteral&            operator =                  (CStringLiteral&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone                       () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CStringLiteral        ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print                       (std::ostream& outStr) const;

                                                    /**
                                                     * String value getter
                                                     * @return string value
                                                     */
                    std::string                     getValue                    () const;
        };

    }
    
}