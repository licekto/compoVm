#include "nodes/procedural/constant.h"

namespace nodes {

	namespace procedural {

		CConstant::CConstant(i32 val)
			: CNode(types::nodeType::CONSTANT),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_intValue(val) {
		}

		void CConstant::print(std::ostream& outStr) const {
			outStr << m_intValue;
		}

		i32 CConstant::getValue() const {
			return m_intValue;
		}
	}

}