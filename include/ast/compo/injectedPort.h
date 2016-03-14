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
			CInjectedPort(ast::types::portType type = ast::types::portType::UNIVERSAL,
			              std::shared_ptr<ast::procedural::CSymbol> name = nullptr,
			              bool atomic = false,
			              std::shared_ptr<ast::procedural::CSymbol> injectedWith = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			 * Injected with getter
			 * @return name symbol of injecting element.
			 */
			std::string getInjectedWith() const;
		};

	}

}