#include "nodes/compo/abstractServConstr.h"

namespace nodes {

	namespace compo {

		CAbstractServConstr::CAbstractServConstr(std::shared_ptr<nodes::compo::CServiceSignature> signature,
		        std::shared_ptr<nodes::procedural::CCompoundBody> body)
			: CNode(types::nodeType::SERVICE),
			  m_signature(signature),
			  m_body(body) {
		}

		void CAbstractServConstr::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << typeName(m_nodeType) << " ";

			outstream << ") {" << std::endl;
			outstream << "\t";
			outstream << "}" << std::endl;
		}

		std::shared_ptr<nodes::procedural::CSymbol> CAbstractServConstr::getNameSymbol() const {
			return m_signature->getName();
		}

		size_t CAbstractServConstr::getBodySize() const {
			if (m_body) {
				return m_body->getBodySize();
			}
			return 0;
		}

		size_t CAbstractServConstr::getTemporariesSize() const {
			if (m_body) {
				return m_body->getTemporariesSize();
			}
			return 0;
		}

		std::shared_ptr<nodes::CNode> CAbstractServConstr::getBodyNodeAt(int index) const {
			if (m_body) {
				return m_body->getBodyNodeAt(index);
			}
			return nullptr;
		}

		void CAbstractServConstr::addBodyNode(std::shared_ptr<nodes::CNode> node) {
			if (m_body) {
				m_body->addBodyNode(node);
			}
		}

		void CAbstractServConstr::addTemporary(std::shared_ptr<nodes::procedural::CSymbol> temporary) {
			if (m_body) {
				m_body->addTemporary(temporary);
			}
		}

		std::shared_ptr<nodes::procedural::CSymbol> CAbstractServConstr::getTemporaryAt(int index) const {
			if (m_body) {
				return m_body->getTemporaryAt(index);
			}
			return nullptr;
		}

		size_t CAbstractServConstr::getParamsSize() const {
			if (m_signature) {
				return m_signature->getParamsSize();
			}
			return 0;
		}

		std::shared_ptr<nodes::CNode> CAbstractServConstr::getParamAt(int index) const {
			if (m_signature) {
				return m_signature->getParamAt(index);
			}
			return nullptr;
		}

		void CAbstractServConstr::setParam(std::shared_ptr<nodes::procedural::CSymbol> param) {
			if (m_signature) {
				return m_signature->setParam(param);
			}
		}

	}

}