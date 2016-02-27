#include "nodes/compo/injectedPort.h"

namespace nodes {

	namespace compo {

		CInjectedPort::CInjectedPort( procedural::CSymbol* name,
		                              bool atomic,
		                              procedural::CSymbol* injectedWith  )
			:   CNode(types::nodeType::INJECTED_PORT),
			    CPort(name, atomic),
			    m_injectedWith(injectedWith) {
		}

		CInjectedPort::CInjectedPort(const CInjectedPort& other)
			: CNode(other),
			  CPort(other),
			  m_injectedWith(new procedural::CSymbol(*other.m_injectedWith)) {
		}

		CInjectedPort::CInjectedPort(CInjectedPort&& other) noexcept
			: CNode(std::move(other)),
			  CPort(std::move(other)),
			  m_injectedWith(other.m_injectedWith) {
			other.m_injectedWith = nullptr;
		}

		CInjectedPort& CInjectedPort::operator =(const CInjectedPort& other) {
			if (&other != this) {
				this->m_nodeType = other.m_nodeType;
				this->m_atomic = other.m_atomic;
				this->m_name = new procedural::CSymbol(*other.m_name);
				this->m_injectedWith = new procedural::CSymbol(*other.m_injectedWith);
			}
			return *this;
		}

		CInjectedPort& CInjectedPort::operator =(CInjectedPort&& other) noexcept {
			if (&other != this) {
				this->m_nodeType = std::move(other.m_nodeType);
				this->m_atomic = std::move(other.m_atomic);
				this->m_name = other.m_name;
				other.m_name = nullptr;
				this->m_injectedWith = other.m_injectedWith;
				other.m_injectedWith = nullptr;
			}
			return *this;
		}

		CNode* CInjectedPort::clone() const {
			return new CInjectedPort(*this);
		}

		CInjectedPort::~CInjectedPort() {
			delete m_injectedWith;
		}

		void CInjectedPort::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << *m_name << " : { }";
		}

		std::string CInjectedPort::getInjectedWith() const {
			if (m_injectedWith) {
				return m_injectedWith->getStringValue();
			}
			return "";
		}
	}

}