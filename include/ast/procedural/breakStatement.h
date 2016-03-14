#pragma once

#include <memory>

#include "ast/procedural/abstractStatement.h"
#include "ast/visitor/abstractStringVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CBreakStatement
		 * \brief Class for break statement representation
		 */
		class CBreakStatement : public CAbstractStatement {
		  public:
			/**
			* Default constructor
                        */
			CBreakStatement();

			/**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);
		};

	}

}