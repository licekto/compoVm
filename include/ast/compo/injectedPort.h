#pragma once

#include <memory>

#include "ast/compo/port.h"

namespace ast {

	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CInjectedPort : public CPort {
		  private:
			/**< Name symbol of injected port */
			std::shared_ptr<ast::procedural::CSymbol> m_injectedWith;

		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of port
			* @param atomic: is atomic
			* @param injectedWith: name of injected port
			*/
			CInjectedPort(std::shared_ptr<ast::procedural::CSymbol> name = nullptr,
			              bool atomic = false,
			              std::shared_ptr<ast::procedural::CSymbol> injectedWith = nullptr);

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			 * Injected with getter
			 * @return name symbol of injecting element.
			 */
			std::shared_ptr<ast::procedural::CSymbol> getInjectedWith() const;
		};

	}

}