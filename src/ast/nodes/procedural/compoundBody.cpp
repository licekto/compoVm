#include "ast/nodes/procedural/compoundBody.h"
#include "logger/logger.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CCompoundBody::CCompoundBody(const std::vector<std::shared_ptr<ast::nodes::procedural::CSymbol> >& temporaries,
			                             const std::vector<std::shared_ptr<ast::nodes::CNode> >& body)
				:   CNode(types::nodeType::COMPOUND_BODY),
				    m_temporaries(temporaries),
				    m_body(body) {
			}

			void CCompoundBody::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<ast::nodes::CNode> CCompoundBody::getBodyNodeAt(int index) const {
				std::shared_ptr<ast::nodes::CNode> node = nullptr;
				try {
					node = m_body.at(index);
				} catch (const std::out_of_range& ex) {
                                        TRACE(ERROR, ex.what());
				}
				return node;
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CCompoundBody::getTemporaryAt(int index) const {
				std::shared_ptr<ast::nodes::procedural::CSymbol> symbol = nullptr;
				try {
					symbol = m_temporaries.at(index);
				} catch (const std::out_of_range& ex) {
					TRACE(ERROR, ex.what());
				}
				return symbol;
			}

			void CCompoundBody::addBodyNode(std::shared_ptr<ast::nodes::CNode> node) {
				m_body.push_back(node);
			}

			void CCompoundBody::addTemporary(std::shared_ptr<ast::nodes::procedural::CSymbol> temporary) {
				m_temporaries.push_back(temporary);
			}

			size_t CCompoundBody::getBodySize() const {
				return m_body.size();
			}

			size_t CCompoundBody::getTemporariesSize() const {
				return m_temporaries.size();
			}
		}
	}
}