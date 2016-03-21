#pragma once

#include <memory>

#include "ast/nodes/compo/port.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CInjectedPort
			 * \brief Class for Compo injected port representation
			 */
			class CInjectedPort : public CPort, public std::enable_shared_from_this<CInjectedPort> {
			  private:
				/**< Name symbol of injected port */
				std::shared_ptr<procedural::CSymbol> m_injectedWith;

			  public:
				/**
				* Parametric constructor with default values
				* @param name: name of port
				* @param atomic: is atomic
				* @param injectedWith: name of injected port
				*/
				CInjectedPort(std::shared_ptr<procedural::CSymbol> name = nullptr,
				              bool atomic = false,
				              std::shared_ptr<procedural::CSymbol> injectedWith = nullptr);

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Injected with getter
				 * @return name symbol of injecting element.
				 */
				std::shared_ptr<procedural::CSymbol> getInjectedWith() const;
			};

		}

	}

}