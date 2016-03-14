#include "ast/compo/architecture.h"
namespace ast {

	namespace compo {

		CArchitecture::CArchitecture(const std::vector<std::shared_ptr<ast::compo::CBind>>& architectureBody)
			: CNode(types::nodeType::ARCHITECTURE),
			  m_architectureBody(architectureBody) {
		}

		void CArchitecture::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

		size_t CArchitecture::getBodySize() const {
			return m_architectureBody.size();
		}

		std::shared_ptr<ast::compo::CBind> CArchitecture::getBodyNodeAt(unsigned int index) const {
			std::shared_ptr<ast::compo::CBind> node = nullptr;
			try {
				node = m_architectureBody.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}
	}
}