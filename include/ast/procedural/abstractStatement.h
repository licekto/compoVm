#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CAbstractStatement
		 * \brief Class for abstract statement representation.
		 */
		class CAbstractStatement : public virtual CNode {
		  public:

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(ast::visitors::CAbstractVisitor *visitor) = 0;
		};

	}

}