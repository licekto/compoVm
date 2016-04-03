#include "ast/nodes/compo/port.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CPort::CPort(ast::nodes::types::portType type, std::shared_ptr<ast::nodes::procedural::CSymbol> name, bool atomicity, bool collectivity)
				:   CNode(types::nodeType::PORT),
				    m_portType(type),
				    m_name(name),
				    m_atomicity(atomicity),
				    m_collectivity(collectivity) {
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CPort::getNameSymbol() const {
				return m_name;
			}

			bool CPort::getAtomicity() const {
				return m_atomicity;
			}

			ast::nodes::types::portType CPort::getPortType() const {
				return m_portType;
			}

			void CPort::setKindOf(std::shared_ptr<ast::nodes::procedural::CSymbol> kindOf) {
				m_kindOf = kindOf;
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CPort::getKindOf() const {
				return m_kindOf;
			}

			bool CPort::isCollection() const {
				return m_collectivity;
                        }

                        void CPort::setVisibility(nodes::types::visibilityType visibility) {
                            m_visibilityType = visibility;
                        }

                        nodes::types::visibilityType CPort::getVisibility() const {
                            return m_visibilityType;
                        }

                        void CPort::setRole(nodes::types::portRoleType role) {
                            m_role = role;
                        }

                        nodes::types::portRoleType CPort::getRole() const {
                            return m_role;
                        }

		}
	}
}