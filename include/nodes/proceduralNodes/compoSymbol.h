#pragma once

#include "nodes/compoNode.h"

namespace compo {
    
    /**
     * \class CCompoSymbol
     * \brief Class for Compo symbol node representation.
     */
    class CCompoSymbol : public CCompoNode {
    private:
                std::string                     m_name;         /**< Name of symbol */

    public:
                                                /**
                                                * Parametric constructor with default value
                                                * @param name: string name
                                                */
                                                CCompoSymbol        (const std::string& name);
                                                
                                                /**
                                                * Copy constructor
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoSymbol        (const CCompoSymbol& other);
                                                
                                                /**
                                                * Move constructor
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoSymbol        (CCompoSymbol&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoSymbol&                   operator=           (const CCompoSymbol& other);
                
                                                /**
                                                * Move assignment operator
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoSymbol&                   operator=           (CCompoSymbol&& other) noexcept;
                                                
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                   () const;
                
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoSymbol       ();
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