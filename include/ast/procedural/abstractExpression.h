#pragma once

#include <memory>
#include "abstractStatement.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	/**
	 *  \addtogroup procedural
	 *  @{
	 */

	/**
	 * procedural Namespace to uniquely identify compo AST nodes.
	 */
	namespace procedural {

		/**
		 * \class CAbstractExpression
		 * \brief Class for abstract expression representation.
		 */
		class CAbstractExpression : public virtual CAbstractStatement {
		  public:

			/**
			  * Accept method for visitor acceptation.
			  * @param visitor: Pointer to abstract visitor.
			  */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor) = 0;
		};

	}

}