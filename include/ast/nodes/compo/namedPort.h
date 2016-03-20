#pragma once

#include <memory>
#include "ast/nodes/compo/port.h"
#include "ast/nodes/procedural/symbol.h"

namespace ast {

    namespace nodes {
        
	namespace compo {

		/**
		 * \class CNamedPort
		 * \brief Class for named port representation.
		 */
		class CNamedPort : public CPort {
		  protected:
			/**< Name parameter symbol of port */
			std::shared_ptr<procedural::CSymbol> m_nameParam;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CNamedPort(std::shared_ptr<procedural::CSymbol> name = nullptr,
			           bool atomicity = false,
			           std::shared_ptr<procedural::CSymbol> nameParam = nullptr,
			           bool collectivity = false);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(visitors::CAbstractVisitor *visitor);

			/**
			 * Signatures getter
			 * @param index
			 * @return shared_ptr to CServiceSignature
			 */
			std::shared_ptr<procedural::CSymbol> getParamName() const;
		};

	}
        
    }

}