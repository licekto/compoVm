#pragma once

#include "nodes/compoNodes/compoPort.h"

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
                                                CCompoInjectedPort      ( CCompoSymbol *name = nullptr,
                                                                          bool atomic = false,
                                                                          CCompoSymbol * injectedWith = nullptr   );
                                                
                                                /**
                                                * Copy constructor
                                                * @param other: reference to another object of same type
                                                */
                                                CCompoInjectedPort      (const CCompoInjectedPort& other);
                                                
                                                /**
                                                * Move constructor
                                                * @param other: rvalue-reference to another object of same type
                                                */
                                                CCompoInjectedPort      (CCompoInjectedPort&& other) noexcept;
                                                
                                                /**
                                                * Copy assignment operator
                                                * @param other: reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoInjectedPort&             operator=               (const CCompoInjectedPort& other);
                
                                                /**
                                                * Move assignment operator
                                                * @param other: rvalue-reference to another object of same type
                                                * @return reference to assigned object
                                                */
                CCompoInjectedPort&             operator=               (CCompoInjectedPort&& other) noexcept;
                
                                                /**
                                                 * Clone method for copy-construction of polymorphic objects
                                                 * @return pointer to newly copied object.
                                                 */
        virtual CCompoNode *                    clone                   () const;
                                                
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
        
                                                /**
                                                 * Injected with getter
                                                 * @return name symbol of injecting element.
                                                 */
                std::string                     getInjectedWith         () const;
    };

}