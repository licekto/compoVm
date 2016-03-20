#pragma once

#include <memory>

#include "ast/nodes/procedural/abstractStatement.h"
#include "ast/nodes/procedural/abstractExpression.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {
    
    namespace nodes {

	namespace procedural {

		/**
		 * \class CReturnStatement
		 * \brief Class for return statement representation
		 */
		class CReturnStatement : public CAbstractStatement, public std::enable_shared_from_this<CReturnStatement> {
		  private:
			/**< Start condition node */
			std::shared_ptr<procedural::CAbstractExpression> m_expression;

		  public:
			/**
			* Parametric constructor with default value
			* @param expression: expression smart pointer
			*/
			CReturnStatement(std::shared_ptr<procedural::CAbstractExpression> expression = nullptr);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<procedural::CAbstractExpression> getExpression() const;
		};

	}
        
    }

}