#pragma once

#include <memory>
#include "ast/procedural/symbol.h"

namespace ast {

	namespace compo {

		/**
		 * \class CNamedPort
		 * \brief Class for named port representation.
		 */
		class CServiceInvocation : public CNode {
		  protected:
			/**< Name of component */
			std::shared_ptr<ast::procedural::CSymbol> m_receiver;

			/**< Name of service */
			std::shared_ptr<ast::procedural::CSymbol> m_selector;

			/**< Parameters of service invocation. Only CServiceSignature or CServiceInvocation nodes allowed. */
			std::shared_ptr<ast::CNode> m_parameters;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CServiceInvocation(std::shared_ptr<ast::procedural::CSymbol> receiver = nullptr,
			                   std::shared_ptr<ast::procedural::CSymbol> selector = nullptr,
			                   std::shared_ptr<ast::CNode> parameters = nullptr);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			 * Signatures getter
			 * @return shared_ptr to CServiceSignature
			 */
			std::shared_ptr<ast::procedural::CSymbol> getReceiverName() const;

			/**
			* Signatures getter
					 * @return shared_ptr to CServiceSignature
					 */
			std::shared_ptr<ast::procedural::CSymbol> getSelectorName() const;

			/**
			* Index expression getter
					 * @return shared_ptr to CAbstractExpression
					 */
			std::shared_ptr<ast::CNode> getParameters() const;
		};

	}

}