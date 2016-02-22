#pragma once

#include "compoNode.h"

namespace compo {
    
    /**
     * \class CCompoArchitecture
     * \brief Class for Compo architecture representation.
     */
    class CCompoArchitecture : public CCompoNode {
    private:

    public:
                                                /**
                                                * Parametric constructor
                                                */
                                                CCompoArchitecture      ();
                                                
                                                /**
                                                * Copy constructor
                                                * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoArchitecture      (const CCompoArchitecture& other);
                                                
                                                /**
                                                * Move constructor
                                                * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoArchitecture      (CCompoArchitecture&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoArchitecture&             operator =              (const CCompoArchitecture& other);
    
                                                /**
                                                * Move assignment operator
                                                * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoArchitecture&             operator =              (CCompoArchitecture&& other) noexcept;
    
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                   () const;
                                                
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoArchitecture     ();
        
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print               (std::ostream& os) const;
    };

}