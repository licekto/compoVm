#pragma once

#include <memory>

#include "ast/nodes/procedural/abstractStatement.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CContinueStatement
			 * \brief Class for continue statement representation
			 */
			class CContinueStatement : public CAbstractStatement, public std::enable_shared_from_this<CContinueStatement> {
			  public:
				/**
				* Default constructor
				            */
				CContinueStatement();

				/**
				            * Accept method for visitor acceptation.
				            * @param visitor: Pointer to abstract visitor.
				            */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);
			};

		}

	}

}