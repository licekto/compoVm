#include "ast/procedural/constant.h"

namespace ast {

	namespace procedural {

		CConstant::CConstant(i32 val)
			: CNode(types::nodeType::CONSTANT),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_intValue(val) {
		}

		void CConstant::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

		i32 CConstant::getValue() const {
			return m_intValue;
		}
	}

}