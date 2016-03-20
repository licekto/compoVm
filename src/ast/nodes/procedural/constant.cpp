#include "ast/nodes/procedural/constant.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CConstant::CConstant(i32 val)
			: CNode(types::nodeType::CONSTANT),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_intValue(val) {
		}

		void CConstant::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		i32 CConstant::getValue() const {
			return m_intValue;
		}
	}
    }
}