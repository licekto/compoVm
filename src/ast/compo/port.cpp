#include "ast/compo/port.h"

namespace ast {

	namespace compo {

		CPort::CPort(ast::types::portType type, std::shared_ptr<ast::procedural::CSymbol> name, bool atomicity, bool collectivity)
			:   CNode(types::nodeType::PORT),
			    m_portType(type),
			    m_name(name),
			    m_atomicity(atomicity),
			    m_collectivity(collectivity) {
		}
                
		std::shared_ptr<ast::procedural::CSymbol> CPort::getNameSymbol() const {
                    return m_name;
		}

		bool CPort::getAtomicity() const {
			return m_atomicity;
		}

		ast::types::portType CPort::getPortType() const {
			return m_portType;
		}

		void CPort::setKindOf(std::shared_ptr<ast::procedural::CSymbol> kindOf) {
			m_kindOf = kindOf;
		}

		std::shared_ptr<ast::procedural::CSymbol> CPort::getKindOf() const {
			return m_kindOf;
		}

		bool CPort::getCollectivity() const {
			return m_collectivity;
		}
	}

}