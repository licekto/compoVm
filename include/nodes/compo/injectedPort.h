#pragma once

#include "nodes/compo/port.h"

namespace nodes {

    namespace compo {

        /**
         * \class CInjectedPort
         * \brief Class for Compo injected port representation
         */
        class CInjectedPort : public CPort {
        private:
                    procedural::CSymbol                  * m_injectedWith;         /**< Name symbol of injected port */

        public:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param name: Name of port
                                                    * @param atomic: Is atomic?
                                                    * @param injectedWith: Name of injected port
                                                    */
                                                    CInjectedPort      ( procedural::CSymbol *name = nullptr,
                                                                              bool atomic = false,
                                                                              procedural::CSymbol * injectedWith = nullptr   );

                                                    /**
                                                    * Copy constructor
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CInjectedPort      (const CInjectedPort& other);

                                                    /**
                                                    * Move constructor
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CInjectedPort      (CInjectedPort&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CInjectedPort&             operator=               (const CInjectedPort& other);

                                                    /**
                                                    * Move assignment operator
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CInjectedPort&             operator=               (CInjectedPort&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone                   () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CInjectedPort     ();

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
    
}