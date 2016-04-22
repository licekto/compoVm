#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/procedural/symbol.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CInjectedPort
			 * \brief Class for Compo injected port representation
			 */
			class CPortAddress : public CNode, public std::enable_shared_from_this<CPortAddress> {
			  private:
				/**< Name symbol of port */
				std::shared_ptr<procedural::CSymbol> m_portName;

				/**< Component node */
				std::shared_ptr<CNode> m_component;

			  public:
				/**
				* Parametric constructor with default values
				* @param name: name of port
				* @param atomic: is atomic
				* @param injectedWith: name of injected port
				*/
				CPortAddress(std::shared_ptr<procedural::CSymbol> portName = nullptr,
				             std::shared_ptr<CNode> component = nullptr);

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Port name getter
				 * @return name symbol of port identification.
				 */
				std::shared_ptr<procedural::CSymbol> getPortName() const;

				/**
				* Component node getter
				                * @return shared pointer to CNode
				                */
				std::shared_ptr<CNode> getComponent() const;
			};

		}

	}

}