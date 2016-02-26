#pragma once

#include "nodes/node.h"
#include "abstractPrimaryExpression.h"


namespace nodes {

    namespace procedural {

        /**
         * \class CSymbol
         * \brief Class for Compo symbol node representation.
         */
        class CSymbol : public CAbstractPrimaryExpression {
        private:
                    std::string                     m_name;         /**< Name of symbol */

        public:
                                                    /**
                                                    * Parametric constructor with default value
                                                    * @param name: string name
                                                    */
                                                    CSymbol        (const std::string& name);

                                                    /**
                                                    * Copy constructor
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CSymbol        (const CSymbol& other);

                                                    /**
                                                    * Move constructor
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CSymbol        (CSymbol&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CSymbol&                   operator=           (const CSymbol& other);

                                                    /**
                                                    * Move assignment operator
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CSymbol&                   operator=           (CSymbol&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone                   () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CSymbol       ();
                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print               (std::ostream& os) const;
                                                    /**
                                                    * StringValue getter
                                                    * @return name string object
                                                    */
                    std::string                     getStringValue      () const;
        };

    }
    
}