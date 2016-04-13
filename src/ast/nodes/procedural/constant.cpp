#include "ast/nodes/procedural/constant.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CConstant::CConstant(u64 val)
				: CNode(types::nodeType::CONSTANT),
				  CAbstractExpression(),
				  CAbstractPrimaryExpression(),
				  m_intValue(val) {
			}

			void CConstant::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			u64 CConstant::getValue() const {
				return m_intValue;
			}
		}
	}
}