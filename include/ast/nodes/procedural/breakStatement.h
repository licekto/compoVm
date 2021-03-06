#pragma once

#include <memory>

#include "ast/nodes/procedural/abstractStatement.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CBreakStatement
			 * \brief Class for break statement representation
			 */
			class CBreakStatement : public CAbstractStatement, public std::enable_shared_from_this<CBreakStatement> {
			  public:
				/**
				* Default constructor
				*/
				CBreakStatement();

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);
			};

		}

	}

}