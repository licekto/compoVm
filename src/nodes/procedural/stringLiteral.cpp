#include "nodes/procedural/stringLiteral.h"

namespace nodes {

	namespace procedural {

		CStringLiteral::CStringLiteral(const std::string& val)
			: CNode(types::nodeType::STRING_LITERAL),
			  m_stringValue(val) {
		}

		void CStringLiteral::print(std::ostream& outStr) const {
			outStr << m_stringValue;
		}

		std::string CStringLiteral::getValue() const {
			return m_stringValue;
		}
	}

}