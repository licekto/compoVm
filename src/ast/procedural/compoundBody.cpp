#include "ast/procedural/compoundBody.h"

namespace ast {

	namespace procedural {

		CCompoundBody::CCompoundBody(const std::vector<std::shared_ptr<ast::procedural::CSymbol> >& temporaries,
		                             const std::vector<std::shared_ptr<ast::CNode> >& body)
			:   CNode(ast::types::nodeType::COMPOUND_BODY),
			    m_temporaries(temporaries),
			    m_body(body) {
		}

		void CCompoundBody::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::CNode> CCompoundBody::getBodyNodeAt(int index) const {
			std::shared_ptr<ast::CNode> node = nullptr;
			try {
				node = m_body.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

		std::shared_ptr<ast::procedural::CSymbol> CCompoundBody::getTemporaryAt(int index) const {
			std::shared_ptr<ast::procedural::CSymbol> symbol = nullptr;
			try {
				symbol = m_temporaries.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return symbol;
		}

		void CCompoundBody::addBodyNode(std::shared_ptr<ast::CNode> node) {
			m_body.push_back(node);
		}

		void CCompoundBody::addTemporary(std::shared_ptr<ast::procedural::CSymbol> temporary) {
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