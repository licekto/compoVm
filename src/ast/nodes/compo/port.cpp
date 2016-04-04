#include "ast/nodes/compo/port.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CPort::CPort(types::portType type, std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			             bool atomicity, bool collectivity, types::visibilityType visibility, types::roleType role)
				:   CNode(types::nodeType::PORT),
				    m_portType(type),
				    m_name(name),
				    m_atomicity(atomicity),
				    m_collectivity(collectivity),
				    m_visibilityType(visibility),
				    m_role(role) {
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CPort::getNameSymbol() const {
				return m_name;
			}

			bool CPort::getAtomicity() const {
				return m_atomicity;
			}

			types::portType CPort::getPortType() const {
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

			void CPort::setVisibility(types::visibilityType visibility) {
				m_visibilityType = visibility;
			}

			types::visibilityType CPort::getVisibility() const {
				return m_visibilityType;
			}

			void CPort::setRole(types::roleType role) {
				m_role = role;
			}

			types::roleType CPort::getRole() const {
				return m_role;
			}

		}
	}
}