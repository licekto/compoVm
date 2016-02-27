#include "nodes/procedural/stringLiteral.h"

namespace nodes {

	namespace procedural {

		CStringLiteral::CStringLiteral(const std::string& val)
			: CNode(types::nodeType::STRING_LITERAL),
			  m_stringValue(val) {
		}

		CStringLiteral::CStringLiteral(const CStringLiteral& other)
			: CNode(other),
			  m_stringValue(other.m_stringValue) {
		}

		CStringLiteral::CStringLiteral(CStringLiteral&& other) noexcept
			: CNode(std::move(other)),
			  m_stringValue(std::move(other.m_stringValue)) {
		}

		CStringLiteral& CStringLiteral::operator =(const CStringLiteral& other) {
			if (&other != this) {
				m_nodeType = other.m_nodeType;
				m_stringValue = other.m_stringValue;
			}
			return *this;
		}

		CStringLiteral& CStringLiteral::operator =(CStringLiteral&& other) noexcept {
			if (&other != this) {
				m_nodeType = std::move(other.m_nodeType);
				m_stringValue = std::move(other.m_stringValue);
			}
			return *this;
		}

		CNode * CStringLiteral::clone() const {
			return new CStringLiteral(*this);
		}

		CStringLiteral::~CStringLiteral() {
		}

		void CStringLiteral::print(std::ostream& outStr) const {
			outStr << m_stringValue;
		}

		std::string CStringLiteral::getValue() const {
			return m_stringValue;
		}
	}

}