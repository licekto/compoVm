#include "ast/procedural/additionExpression.h"

namespace ast {

	namespace procedural {

		CAdditionExpression::CAdditionExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::ADDITION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::PLUS, op1, op2) {
		}

		void CAdditionExpression::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}