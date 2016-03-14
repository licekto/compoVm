#pragma once

#include <memory>
#include "types.h"
#include "abstractPrimaryExpression.h"
#include "ast/visitor/abstractStringVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CConstant
		 * \brief Class for integer literal representation.
		 *
		 * Class contains positive or negative 4B integer value.
		 */
		class CConstant : public CAbstractPrimaryExpression {
		  private:
			/**< Integer 4B value */
			i32 m_intValue;

		  public:
			/**
			* Parametric constructor with default value
			* @param val: integer value
			*/
			CConstant(i32 val = 0);

			/**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);

			/**
			 * Integer value getter
			 * @return integer value
			 */
			i32 getValue() const;
		};

	}

}