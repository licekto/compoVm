#include "ast/nodes/compo/service.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CService::CService(std::shared_ptr<ast::nodes::compo::CServiceSignature> signature,
			                   std::shared_ptr<ast::nodes::procedural::CStringLiteral> code)
				: CNode(ast::nodes::types::nodeType::SERVICE),
				  m_signature(signature),
				  m_code(code),
				  m_body(nullptr) {
			}

			void CService::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			void CService::checkBodyCompiled() const {
				if (!m_body.use_count()) {
					std::string name = "unknown";
					if (m_signature.use_count()) {
						name = m_signature->getNameSymbol()->getStringValue();
					}
					throw exceptions::runtime::CServiceNotCompiledException(name);
				}
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CService::getNameSymbol() const {
				return m_signature->getNameSymbol();
			}

			void CService::setBodyNode(std::shared_ptr<procedural::CCompoundBody> body) {
				m_body = body;
			}

			size_t CService::getBodySize() const {
				checkBodyCompiled();
				return m_body->getBodySize();
			}

			size_t CService::getTemporariesSize() const {
				checkBodyCompiled();
				return m_body->getTemporariesSize();
			}

			std::shared_ptr<ast::nodes::CNode> CService::getBodyNodeAt(int index) const {
				checkBodyCompiled();
				return m_body->getBodyNodeAt(index);
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CService::getTemporaryAt(int index) const {
				checkBodyCompiled();
				return m_body->getTemporaryAt(index);
			}

			size_t CService::getParamsSize() const {
				if (m_signature.use_count()) {
					return m_signature->getParamsSize();
				}
				return 0;
			}

			std::shared_ptr<ast::nodes::CNode> CService::getParamAt(int index) const {
				if (m_signature.use_count()) {
					return m_signature->getParamAt(index);
				}
				return nullptr;
			}

			void CService::setParam(std::shared_ptr<ast::nodes::procedural::CSymbol> param) {
				if (m_signature.use_count()) {
					return m_signature->setParam(param);
				}
			}

			std::string CService::getBodyCode() const {
				if (m_code.use_count()) {
					return m_code->getValue();
				}
				return "";
                        }

                        std::shared_ptr<compo::CServiceSignature> CService::getSignature() const {
                            return m_signature;
                        }

		}

	}

}