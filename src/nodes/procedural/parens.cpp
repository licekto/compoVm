#include "nodes/procedural/parens.h"

namespace nodes {

	namespace procedural {

		CParens::CParens(std::shared_ptr<nodes::CNode> expr)
			: CNode(types::nodeType::PARENS),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_expression(expr) {
		}

		void CParens::print(std::ostream& outStr) const {
			outStr << m_expression;
		}

		std::shared_ptr<nodes::CNode> CParens::getExpression() const {
			return m_expression;
		}
	}

}