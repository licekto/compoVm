#include "ast/compo/descriptor.h"

namespace ast {

	namespace compo {

		CDescriptor::CDescriptor(std::shared_ptr<ast::procedural::CSymbol> name,
		                         std::shared_ptr<ast::procedural::CSymbol> extends,
		                         std::shared_ptr<ast::compo::CProvision> inProv,
		                         std::shared_ptr<ast::compo::CProvision> exProv,
		                         std::shared_ptr<ast::compo::CRequirement> inReq,
		                         std::shared_ptr<ast::compo::CRequirement> exReq,
		                         std::shared_ptr<ast::compo::CArchitecture> arch,
		                         const std::vector<std::shared_ptr<ast::compo::CService>>& services,
		                         const std::vector<std::shared_ptr<ast::compo::CConstraint>>& constraints)
			: CNode(types::nodeType::DESCRIPTOR),
			  m_name(name),
			  m_extends(extends),
			  m_interalProvision(inProv),
			  m_exteralProvision(exProv),
			  m_interalRequirement(inReq),
			  m_exteralRequirement(exReq),
			  m_architecture(arch),
			  m_services(services),
			  m_constraints(constraints),
			  m_defaultPort(std::make_shared<ast::compo::CSignaturesPort>(std::make_shared<ast::procedural::CSymbol>("default"),
			                false,
			                std::vector<std::shared_ptr<ast::compo::CServiceSignature>>(0))) {
		}

		void CDescriptor::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::procedural::CSymbol> CDescriptor::getNameSymbol() const {
			return m_name;
		}

		std::shared_ptr<ast::procedural::CSymbol> CDescriptor::getExtendsSymbol() const {
			return m_extends;
		}

		size_t CDescriptor::getServicesSize() const {
			return m_services.size();
		}

		std::shared_ptr<ast::compo::CService> CDescriptor::getServiceAt(int index) const {
			std::shared_ptr<ast::compo::CService> node;
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

		std::shared_ptr<ast::compo::CConstraint> CDescriptor::getConstraintAt(int index) const {
			std::shared_ptr<ast::compo::CConstraint> node;
			try {
				node = m_constraints.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

		std::shared_ptr<ast::compo::CProvision> CDescriptor::getInProvision() const {
			return m_interalProvision;
		}

		std::shared_ptr<ast::compo::CProvision> CDescriptor::getExProvision() const {
			return m_exteralProvision;
		}

		std::shared_ptr<ast::compo::CRequirement> CDescriptor::getInRequirement() const {
			return m_interalRequirement;
		}

		std::shared_ptr<ast::compo::CRequirement> CDescriptor::getExRequirement() const {
			return m_exteralRequirement;
		}

		std::shared_ptr<ast::compo::CArchitecture> CDescriptor::getArchitecture() const {
			return m_architecture;
		}

		std::shared_ptr<ast::compo::CPort> CDescriptor::getDefaultPort() const {
			return m_defaultPort;
		}
	}

}