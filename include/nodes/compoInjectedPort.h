#pragma once

#include "compoPort.h"

namespace compo {
    
    /**
     * \class CCompoInjectedPort
     * \brief Class for Compo injected port representation
     */
    class CCompoInjectedPort : public CCompoPort {
    private:
                CCompoSymbol                  * m_injectedWith;         /**< Name symbol of injected port */

    public:
                                                /**
                                                * Parametric constructor with default values
                                                * @param name: Name of port
                                                * @param atomic: Is atomic?
                                                * @param injectedWith: Name of injected port
                                                */
                                                CCompoInjectedPort      (   CCompoSymbol *name = nullptr,
                                                                            bool atomic = false,
                                                                            CCompoSymbol * injectedWith = nullptr   );
                                                /**
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoInjectedPort     ();
                                                /**
                                                * Virtual print function to call from operator <<
                                                * @param os: output stream
                                                * @see operator <<()
                                                */
        virtual void                            print                   (std::ostream& os) const;
    };

}