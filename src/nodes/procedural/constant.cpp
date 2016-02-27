#include "nodes/procedural/constant.h"

namespace nodes {

	namespace procedural {

		CConstant::CConstant(i32 val)
			: CNode(types::nodeType::CONSTANT),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_intValue(val) {
		}

		CConstant::CConstant(const CConstant& other)
			: CNode(other),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_intValue(other.m_intValue) {
		}

		CConstant::CConstant(CConstant&& other) noexcept
			: CNode(std::move(other)),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_intValue(std::move(other.m_intValue)) {
		}

		CConstant& CConstant::operator =(const CConstant& other) {
			if (&other != this) {
				m_nodeType = other.m_nodeType;
				m_intValue = other.m_intValue;
			}
			return *this;
		}

		CConstant& CConstant::operator =(CConstant&& other) noexcept {
			if (&other != this) {
				m_nodeType = std::move(other.m_nodeType);
				m_intValue = std::move(other.m_intValue);
			}
			return *this;
		}

		CNode * CConstant::clone() const {
			return new CConstant(*this);
		}

		CConstant::~CConstant() {
		}

		void CConstant::print(std::ostream& outStr) const {
			outStr << m_intValue;
		}

		i32 CConstant::getValue() const {
			return m_intValue;
		}
	}

}