#pragma once

#include <memory>
#include "ast/nodes/procedural/symbol.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CNamedPort
			 * \brief Class for named port representation.
			 */
			class CCollectionPortLiteral : public CNode, public std::enable_shared_from_this<CCollectionPortLiteral> {
			  protected:
				/**< Name parameter symbol of port */
				std::shared_ptr<procedural::CSymbol> m_portName;

				/**< Index expression */
				std::shared_ptr<procedural::CAbstractExpression> m_indexExpression;

			  public:
				/**
				* Parametric constructor with default value
				* @param name: Name of port
				* @param atomic: Is atomic?
				*/
				CCollectionPortLiteral(std::shared_ptr<procedural::CSymbol> portName = nullptr,
				                       std::shared_ptr<procedural::CAbstractExpression> indexExpression = nullptr);

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Signatures getter
				 * @return shared_ptr to CServiceSignature
				 */
				std::shared_ptr<procedural::CSymbol> getPortName() const;

				/**
				* Index expression getter
						 * @return shared_ptr to CAbstractExpression
						 */
				std::shared_ptr<procedural::CAbstractExpression> getIndexExpression() const;
			};

		}

	}

}