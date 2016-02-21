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
                                                * Virtual destructor
                                                */
        virtual                                 ~CCompoArchitecture     ();
    };

}