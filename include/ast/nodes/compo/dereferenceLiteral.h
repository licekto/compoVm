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
			class CDereferenceLiteral : public CNode, public std::enable_shared_from_this<CDereferenceLiteral> {
			  protected:
				/**< Name parameter symbol of port */
				std::shared_ptr<procedural::CSymbol> m_parameter;

			  public:
				/**
				* Parametric constructor with default value
				* @param name: Name of port
				* @param atomic: Is atomic?
				*/
				CDereferenceLiteral(std::shared_ptr<procedural::CSymbol> parameter = nullptr);

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Signatures getter
				 * @return shared_ptr to CServiceSignature
				 */
				std::shared_ptr<procedural::CSymbol> getParamName() const;
			};

		}

	}

}