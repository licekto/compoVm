#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace procedural {

		CSymbol::CSymbol(const std::string& name)
			: CNode(types::nodeType::SYMBOL),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_name(name) {
		}

		CSymbol::CSymbol(const CSymbol& other)
			: CNode(other),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_name(other.m_name) {
		}

		CSymbol::CSymbol(CSymbol&& other) noexcept
			: CNode(std::move(other)),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_name(std::move(other.m_name)) {
			other.m_name.clear();
		}

		CSymbol& CSymbol::operator= (const CSymbol& other) {
			if (&other != this) {
				this->m_nodeType = other.m_nodeType;
				this->m_name = other.m_name;
			}
			return *this;
		}

		CSymbol& CSymbol::operator= (CSymbol&& other) noexcept {
			if (&other != this) {
				this->m_nodeType = std::move(other.m_nodeType);
				this->m_name = std::move(other.m_name);
				other.m_name.clear();
			}
			return *this;
		}

		CNode * CSymbol::clone() const {
			return new CSymbol(*this);
		}

		CSymbol::~CSymbol() {
		}

		void CSymbol::print(std::ostream& outstream) const {
			outstream << m_name;
		}

		std::string CSymbol::getStringValue() const {
			return m_name;
		}

	}

}