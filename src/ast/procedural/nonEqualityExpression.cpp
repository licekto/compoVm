#include "ast/procedural/nonEqualityExpression.h"

namespace ast {

	namespace procedural {

		CNonEqualityExpression::CNonEqualityExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::NON_EQUALITY_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::NON_EQUALITY, op1, op2) {
		}

		void CNonEqualityExpression::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}