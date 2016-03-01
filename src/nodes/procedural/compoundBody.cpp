#include "nodes/procedural/compoundBody.h"

namespace nodes {

	namespace procedural {

		CCompoundBody::CCompoundBody(const std::vector<std::shared_ptr<nodes::procedural::CSymbol> >& temporaries,
		                             const std::vector<std::shared_ptr<nodes::CNode> >& body)
			:   CNode(nodes::types::nodeType::COMPOUND_BODY),
			    m_temporaries(temporaries),
			    m_body(body) {
		}

		void CCompoundBody::print(std::ostream& outstream) const {
			outstream << "\t{";
			if (m_temporaries.size() != 0) {
				outstream << "| ";
				for (std::shared_ptr<nodes::procedural::CSymbol> symbol : m_temporaries) {
					outstream << "\t\t";
					outstream << *symbol << " ";
				}
				outstream << "|" << std::endl;
			}
			if (m_body.size() != 0) {
				for (std::shared_ptr<nodes::CNode> expr : m_body) {
					outstream << "\t\t";
					outstream << *expr;
				}
			}
			outstream << "}" << std::endl;
		}

		std::shared_ptr<nodes::CNode> CCompoundBody::getBodyNodeAt(int index) const {
			std::shared_ptr<nodes::CNode> node = nullptr;
			try {
				node = m_body.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

		std::shared_ptr<nodes::procedural::CSymbol> CCompoundBody::getTemporaryAt(int index) const {
			std::shared_ptr<nodes::procedural::CSymbol> symbol = nullptr;
			try {
				symbol = m_temporaries.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return symbol;
		}
	}

}