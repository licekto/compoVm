#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace procedural {

		CSymbol::CSymbol(const std::string& name)
			: CNode(types::nodeType::SYMBOL),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_name(name) {
		}

		void CSymbol::print(std::ostream& outstream) const {
			outstream << m_name;
		}

		std::string CSymbol::getStringValue() const {
			return m_name;
		}

	}

}