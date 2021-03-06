#pragma once

#include <memory>
#include "ast/nodes/procedural/symbol.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CServiceInvocation
			 * \brief Class for service invocation representation.
			 */
			class CServiceInvocation : public CNode, public std::enable_shared_from_this<CServiceInvocation> {
			  protected:
				/**< Name of component */
				std::shared_ptr<procedural::CSymbol> m_receiver;

				/**< Name of service */
				std::shared_ptr<procedural::CSymbol> m_selector;

				/**< Parameters of service invocation. Only CServiceSignature or CServiceInvocation nodes allowed. */
				std::shared_ptr<CNode> m_parameters;

				/**< Index for collection port call */
				std::shared_ptr<CNode> m_index;

			  public:
				/**
				* Parametric constructor with default value
				* @param receiver: name of receiver
				* @param selector: name of selector
				                * @param parameters: node with parameters
				                * @param index: Index for collection port call
				*/
				CServiceInvocation(std::shared_ptr<procedural::CSymbol> receiver = nullptr,
				                   std::shared_ptr<procedural::CSymbol> selector = nullptr,
				                   std::shared_ptr<CNode> parameters = nullptr,
				                   std::shared_ptr<CNode> index = nullptr);

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Signatures getter
				 * @return shared_ptr to CServiceSignature
				 */
				std::shared_ptr<procedural::CSymbol> getReceiverName() const;

				/**
				* Signatures getter
				                * @return shared_ptr to CServiceSignature
				                */
				std::shared_ptr<procedural::CSymbol> getSelectorName() const;

				/**
				* Parameters getter
				                * @return shared_ptr to CNode
				                */
				std::shared_ptr<CNode> getParameters() const;

				/**
				* Index expression getter
				                            * @return shared_ptr to CAbstractExpression
				                            */
				std::shared_ptr<CNode> getIndex() const;
			};

		}

	}

}