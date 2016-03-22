#include "ast/nodes/compo/descriptor.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CDescriptor::CDescriptor(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			                         std::shared_ptr<ast::nodes::procedural::CSymbol> extends,
			                         std::shared_ptr<ast::nodes::compo::CProvision> inProv,
			                         std::shared_ptr<ast::nodes::compo::CProvision> exProv,
			                         std::shared_ptr<ast::nodes::compo::CRequirement> inReq,
			                         std::shared_ptr<ast::nodes::compo::CRequirement> exReq,
			                         std::shared_ptr<ast::nodes::compo::CArchitecture> arch,
			                         const std::vector<std::shared_ptr<ast::nodes::compo::CService>>& services,
			                         const std::vector<std::shared_ptr<ast::nodes::compo::CConstraint>>& constraints)
				: CNode(types::nodeType::DESCRIPTOR),
				  CAbstractDescriptorInterface(name, extends),
				  m_interalProvision(inProv),
				  m_exteralProvision(exProv),
				  m_interalRequirement(inReq),
				  m_exteralRequirement(exReq),
				  m_architecture(arch),
				  m_services(services),
				  m_constraints(constraints),
				  m_defaultPort(std::make_shared<ast::nodes::compo::CSignaturesPort>(std::make_shared<ast::nodes::procedural::CSymbol>("default"),
				                false,
				                std::vector<std::shared_ptr<ast::nodes::compo::CServiceSignature>>(0))) {
			}

			void CDescriptor::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			size_t CDescriptor::getServicesSize() const {
				return m_services.size();
			}

			std::shared_ptr<ast::nodes::compo::CService> CDescriptor::getServiceAt(int index) const {
				std::shared_ptr<ast::nodes::compo::CService> node;
				try {
					node = m_services.at(index);
				} catch (std::out_of_range ex) {
					// log error message
				}
				return node;
			}

			size_t CDescriptor::getConstraintsSize() const {
				return m_constraints.size();
			}

			std::shared_ptr<ast::nodes::compo::CConstraint> CDescriptor::getConstraintAt(int index) const {
				std::shared_ptr<ast::nodes::compo::CConstraint> node;
				try {
					node = m_constraints.at(index);
				} catch (std::out_of_range ex) {
					// log error message
				}
				return node;
			}

			std::shared_ptr<ast::nodes::compo::CProvision> CDescriptor::getInProvision() const {
				return m_interalProvision;
			}

			std::shared_ptr<ast::nodes::compo::CProvision> CDescriptor::getExProvision() const {
				return m_exteralProvision;
			}

			std::shared_ptr<ast::nodes::compo::CRequirement> CDescriptor::getInRequirement() const {
				return m_interalRequirement;
			}

			std::shared_ptr<ast::nodes::compo::CRequirement> CDescriptor::getExRequirement() const {
				return m_exteralRequirement;
			}

			std::shared_ptr<ast::nodes::compo::CArchitecture> CDescriptor::getArchitecture() const {
				return m_architecture;
			}

			std::shared_ptr<ast::nodes::compo::CPort> CDescriptor::getDefaultPort() const {
				return m_defaultPort;
			}
                        
                        std::shared_ptr<ast::nodes::compo::CPort> CDescriptor::getSelfPort() const {
				return m_selfPort;
			}
		}
	}
}