#pragma once

#include <memory>
#include "ast/nodes/compo/port.h"
#include "ast/nodes/procedural/symbol.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		/**
		 * \class CUniversalPort
		 * \brief Class for universal port representation.
		 */
		class CUniversalPort : public CPort {
		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CUniversalPort(std::shared_ptr<procedural::CSymbol> name = nullptr,
			               bool atomicity = false,
			               bool collectivity = false);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(visitors::CAbstractVisitor *visitor);
		};

	}
        
    }

}