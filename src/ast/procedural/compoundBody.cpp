#include "ast/procedural/compoundBody.h"

namespace ast {

	namespace procedural {

		CCompoundBody::CCompoundBody(const std::vector<std::shared_ptr<ast::procedural::CSymbol> >& temporaries,
		                             const std::vector<std::shared_ptr<ast::CNode> >& body)
			:   CNode(ast::types::nodeType::COMPOUND_BODY),
			    m_temporaries(temporaries),
			    m_body(body) {
		}

		void CCompoundBody::print(std::ostream& outstream) const {
			outstream << "\t{";
			if (m_temporaries.size() != 0) {
				outstream << "| ";
				for (std::shared_ptr<ast::procedural::CSymbol> symbol : m_temporaries) {
					outstream << "\t\t";
					outstream << *symbol << " ";
				}
				outstream << "|" << std::endl;
			}
			if (m_body.size() != 0) {
				for (std::shared_ptr<ast::CNode> expr : m_body) {
					outstream << "\t\t";
					outstream << *expr;
				}
			}
			outstream << "}" << std::endl;
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