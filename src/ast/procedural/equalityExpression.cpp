#include "ast/procedural/equalityExpression.h"

namespace ast {

	namespace procedural {

		CEqualityExpression::CEqualityExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::EQUALITY_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::EQUALITY, op1, op2) {
		}

		void CEqualityExpression::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}