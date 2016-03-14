#pragma once

#include <memory>

#include "ast/procedural/abstractStatement.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CContinueStatement
		 * \brief Class for continue statement representation
		 */
		class CContinueStatement : public CAbstractStatement {
		  public:
			/**
			* Default constructor
			            */
			CContinueStatement();

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);
		};

	}

}