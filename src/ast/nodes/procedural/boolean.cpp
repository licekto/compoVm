#include "ast/nodes/procedural/boolean.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CBoolean::CBoolean(bool val)
				: CNode(types::nodeType::BOOLEAN),
				  CAbstractExpression(),
				  CAbstractPrimaryExpression(),
				  m_value(val) {
			}

			void CBoolean::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			bool CBoolean::getValue() const {
				return m_value;
			}
		}
	}
}