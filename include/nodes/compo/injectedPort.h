#pragma once

#include <memory>
#include "nodes/compo/port.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CInjectedPort : public CPort {
		  private:
			std::shared_ptr<nodes::procedural::CSymbol>  m_injectedWith;         /**< Name symbol of injected port */

		  public:
			/**
			* Parametric constructor with default values
			* @param name: Name of port
			* @param atomic: Is atomic?
			* @param injectedWith: Name of injected port
			*/
			CInjectedPort      ( std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
			                     bool atomic = false,
			                     std::shared_ptr<nodes::procedural::CSymbol> injectedWith = nullptr   );

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