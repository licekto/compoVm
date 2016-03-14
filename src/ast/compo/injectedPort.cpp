#include "ast/compo/injectedPort.h"

namespace ast {

	namespace compo {

		CInjectedPort::CInjectedPort( ast::types::portType type,
		                              std::shared_ptr<ast::procedural::CSymbol> name,
		                              bool atomic,
		                              std::shared_ptr<ast::procedural::CSymbol> injectedWith  )
			:   CNode(types::nodeType::INJECTED_PORT),
			    CPort(type, name, atomic),
			    m_injectedWith(injectedWith) {
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