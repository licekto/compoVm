#pragma once

#include <memory>
#include "ast/nodes/procedural/symbol.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CDereferenceLiteral
			 * \brief Class for dereference literal representation.
			 */
			class CDereferenceLiteral : public CNode, public std::enable_shared_from_this<CDereferenceLiteral> {
			  protected:
				/**< Name parameter symbol of port */
				std::shared_ptr<procedural::CSymbol> m_parameter;

			  public:
				/**
				* Parametric constructor with default value
				* @param parameter: dereference parameter
				*/
				CDereferenceLiteral(std::shared_ptr<procedural::CSymbol> parameter = nullptr);

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Name getter
				 * @return shared_ptr to CSymbol
				 */
				std::shared_ptr<procedural::CSymbol> getParamName() const;
			};

		}

	}

}