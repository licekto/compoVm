#include "nodes/compo/port.h"

namespace nodes {

	namespace compo {

		CPort::CPort(procedural::CSymbol* name, bool atomic)
			:   CNode(types::nodeType::PORT),
			    m_name(name), m_atomic(atomic) {
		}

		CPort::CPort(const CPort& other)
			: CNode(other),
			  m_name(new procedural::CSymbol(*other.m_name)),
			  m_atomic(other.m_atomic) {
		}

		CPort::CPort(CPort&& other) noexcept
			: CNode(std::move(other)),
			  m_name(other.m_name),
			  m_atomic(std::move(other.m_atomic)) {
			other.m_name = nullptr;
		}

		CPort& CPort::operator =(const CPort& other) {
			if (&other != this) {
				this->m_nodeType = other.m_nodeType;
				this->m_atomic = other.m_atomic;
				this->m_name = new procedural::CSymbol(*other.m_name);
			}
			return *this;
		}

		CPort& CPort::operator =(CPort&& other) noexcept {
			if (&other != this) {
				this->m_nodeType = std::move(other.m_nodeType);
				this->m_atomic = std::move(other.m_atomic);
				this->m_name = other.m_name;
				other.m_name = nullptr;
			}
			return *this;
		}

		CNode* CPort::clone() const {
			return new CPort(*this);
		}


		CPort::~CPort() {
			delete m_name;
		}

		void CPort::print(std::ostream& outstream) const {
			if (m_name) {
				outstream << "\t";
				outstream << *m_name << " : { }";
			}
		}

		std::string CPort::getName() const {
			if (m_name) {
				return m_name->getStringValue();
			}
			return "";
		}

		bool CPort::getAtomic() const {
			return m_atomic;
		}

	}

}