#include "ast/procedural/logicalOrExpression.h"

namespace ast {

	namespace procedural {

		CLogicalOrExpression::CLogicalOrExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LOGICAL_OR_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LOGICAL_OR, op1, op2) {
		}

		void CLogicalOrExpression::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}