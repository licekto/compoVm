#pragma once

#include <memory>
#include "abstractPrimaryExpression.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CStringLiteral
		 * \brief Class for integer literal representation.
		 *
		 * Class contains positive or negative 4B integer value.
		 */
		class CStringLiteral : public CAbstractPrimaryExpression {
		  private:
			/**< String value */
			std::string m_stringValue;

		  public:
			/**
			* Parametric constructor with default value
			* @param val: string value
			*/
			CStringLiteral(const std::string& val = "");

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			 * String value getter
			 * @return string value
			 */
			std::string getValue() const;
		};

	}

}