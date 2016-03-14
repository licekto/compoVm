#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/procedural/symbol.h"

namespace ast {

	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CPortAddress : public CNode {
		  private:
			/**< Name symbol of port */
			std::shared_ptr<ast::procedural::CSymbol> m_portName;

			/**< Component node */
			std::shared_ptr<ast::CNode> m_component;

		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of port
			* @param atomic: is atomic
			* @param injectedWith: name of injected port
			*/
			CPortAddress(std::shared_ptr<ast::procedural::CSymbol> portName = nullptr,
			             std::shared_ptr<ast::CNode> component = nullptr);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			 * Port name getter
			 * @return name symbol of port identification.
			 */
			std::shared_ptr<ast::procedural::CSymbol> getPortName() const;

			/**
			* Component node getter
					 * @return shared pointer to CNode
					 */
			std::shared_ptr<ast::CNode> getComponent() const;
		};

	}

}