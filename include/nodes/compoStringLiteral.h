#pragma once

#include "compoNode.h"
#include "types.h"

namespace compo {

    /**
     * \class CCompoIntegerLiteral
     * \brief Class for integer literal representation.
     * 
     * Class contains positive or negative 4B integer value.
     */
    class CCompoStringLiteral : public CCompoNode {
    private:
                std::string                     m_stringValue;         /**< String value */
        
    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param type: type of node
                                                * @param val: integer value
                                                */
                                                CCompoStringLiteral         (const std::string& val = "");
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoStringLiteral         (const CCompoStringLiteral& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoStringLiteral         (CCompoStringLiteral&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoStringLiteral&            operator =                  (const CCompoStringLiteral& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoStringLiteral&            operator =                  (CCompoStringLiteral&& other) noexcept;

                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                       () const;
        
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoStringLiteral        ();
        
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print                       (std::ostream& outStr) const;
        
                                                /**
                                                 * Integer value getter
                                                 * @return integer value
                                                 */
                std::string                     getValue                    () const;
    };

}