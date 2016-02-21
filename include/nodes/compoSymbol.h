#pragma once

#include "compoNode.h"

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