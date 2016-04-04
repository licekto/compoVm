#include "ast/nodes/compo/descriptor.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CDescriptor::CDescriptor(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			                         std::shared_ptr<ast::nodes::procedural::CSymbol> extends,
			                         std::shared_ptr<ast::nodes::compo::CArchitecture> arch,
			                         const std::vector<std::shared_ptr<ast::nodes::compo::CPort>>& ports,
			                         const std::vector<std::shared_ptr<ast::nodes::compo::CService>>& services,
			                         const std::vector<std::shared_ptr<ast::nodes::compo::CConstraint>>& constraints)
				: CNode(types::nodeType::DESCRIPTOR),
				  CAbstractDescriptorInterface(name, extends),
				  m_architecture(arch),
				  m_ports(ports),
				  m_services(services),
				  m_constraints(constraints) {
			}

			void CDescriptor::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			size_t CDescriptor::getServicesSize() const {
				return m_services.size();
			}

			size_t CDescriptor::getPortsSize() const {
				return m_ports.size();
			}

			std::shared_ptr<ast::nodes::compo::CService> CDescriptor::getServiceAt(size_t index) const {
				std::shared_ptr<ast::nodes::compo::CService> node;
				try {
					node = m_services.at(index);
				} catch (const std::out_of_range& ex) {
					// log error message
				}
				return node;
			}

			size_t CDescriptor::getConstraintsSize() const {
				return m_constraints.size();
			}

			std::shared_ptr<ast::nodes::compo::CConstraint> CDescriptor::getConstraintAt(size_t index) const {
				std::shared_ptr<ast::nodes::compo::CConstraint> node;
				try {
					node = m_constraints.at(index);
				} catch (const std::out_of_range& ex) {
					// log error message
				}
				return node;
			}

			std::shared_ptr<compo::CPort> CDescriptor::getPortAt(size_t index) const {
				if (index < m_ports.size()) {
					return m_ports.at(index);
				}
				// throw
				return nullptr;
			}

			std::shared_ptr<compo::CPort> CDescriptor::getPortByName(const std::string& name) const {
				auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name] (std::shared_ptr<CPort> port) {
					return port->getNameSymbol()->getStringValue() == name;
				});

				if (it == m_ports.end()) {
					return nullptr;
				}
				return *it;
			}

			std::shared_ptr<ast::nodes::compo::CArchitecture> CDescriptor::getArchitecture() const {
				return m_architecture;
			}

			std::shared_ptr<compo::CService> CDescriptor::getServiceByName(const std::string& name) const {
				auto it = std::find_if(m_services.begin(), m_services.end(), [&name] (std::shared_ptr<CService> srv) {
					return srv->getNameSymbol()->getStringValue() == name;
				});

				if (it == m_services.end()) {
					return nullptr;
				}
				return *it;
			}

		}
	}
}