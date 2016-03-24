#include "ast/nodes/compo/constraint.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CConstraint::CConstraint(std::shared_ptr<CServiceSignature> signature,
			                         std::shared_ptr<procedural::CCompoundBody> body)
				:   CNode(types::nodeType::CONSTRAINT),
				    m_signature(signature),
				    m_body(body) {
			}

			void CConstraint::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<procedural::CSymbol> CConstraint::getNameSymbol() const {
				return m_signature->getNameSymbol();
			}

			size_t CConstraint::getBodySize() const {
				if (m_body) {
					return m_body->getBodySize();
				}
				return 0;
			}

			std::shared_ptr<ast::nodes::CNode> CConstraint::getBodyNodeAt(int index) const {
				if (m_body) {
					return m_body->getBodyNodeAt(index);
				}
				return nullptr;
			}

			void CConstraint::addBodyNode(std::shared_ptr<ast::nodes::CNode> node) {
				if (m_body) {
					m_body->addBodyNode(node);
				}
			}

			size_t CConstraint::getParamsSize() const {
				if (m_signature) {
					return m_signature->getParamsSize();
				}
				return 0;
			}

			std::shared_ptr<ast::nodes::CNode> CConstraint::getParamAt(int index) const {
				if (m_signature) {
					return m_signature->getParamAt(index);
				}
				return nullptr;
			}

			void CConstraint::setParam(std::shared_ptr<ast::nodes::procedural::CSymbol> param) {
				if (m_signature) {
					return m_signature->setParam(param);
				}
			}

		}
	}
}