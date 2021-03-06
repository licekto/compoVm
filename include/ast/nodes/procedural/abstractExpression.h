#pragma once

#include <memory>
#include "ast/nodes/procedural/abstractStatement.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {
		/**
		 *  \addtogroup procedural
		 *  @{
		 */

		/**
		 * procedural Namespace to uniquely identify procedural compo AST nodes.
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
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) = 0;
			};

		}

	}

}