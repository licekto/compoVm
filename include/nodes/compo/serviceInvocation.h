#pragma once

#include <memory>
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CNamedPort
		 * \brief Class for named port representation.
		 */
		class CServiceInvocation : public CNode {
		  protected:
			/**< Name of component */
			std::shared_ptr<nodes::procedural::CSymbol> m_receiver;

			/**< Name of service */
			std::shared_ptr<nodes::procedural::CSymbol> m_selector;

			/**< Parameters of service invocation. Only CServiceSignature or CServiceInvocation nodes allowed. */
			std::shared_ptr<nodes::CNode> m_parameters;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CServiceInvocation(std::shared_ptr<nodes::procedural::CSymbol> receiver = nullptr,
			                   std::shared_ptr<nodes::procedural::CSymbol> selector = nullptr,
			                   std::shared_ptr<nodes::CNode> parameters = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			 * Signatures getter
			 * @return shared_ptr to CServiceSignature
			 */
			std::shared_ptr<nodes::procedural::CSymbol> getReceiverName() const;

			/**
			* Signatures getter
					 * @return shared_ptr to CServiceSignature
					 */
			std::shared_ptr<nodes::procedural::CSymbol> getSelectorName() const;

			/**
			* Index expression getter
					 * @return shared_ptr to CAbstractExpression
					 */
			std::shared_ptr<nodes::CNode> getParameters() const;
		};

	}

}