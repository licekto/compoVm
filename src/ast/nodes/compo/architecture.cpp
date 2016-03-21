#include "ast/nodes/compo/architecture.h"
namespace ast {

	namespace nodes {

		namespace compo {

			CArchitecture::CArchitecture(const std::vector<std::shared_ptr<ast::nodes::compo::CBind>>& architectureBody)
				: CNode(types::nodeType::ARCHITECTURE),
				  m_architectureBody(architectureBody) {
			}

			void CArchitecture::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			size_t CArchitecture::getBodySize() const {
				return m_architectureBody.size();
			}

			std::shared_ptr<ast::nodes::compo::CBind> CArchitecture::getBodyNodeAt(unsigned int index) const {
				std::shared_ptr<ast::nodes::compo::CBind> node = nullptr;
				try {
					node = m_architectureBody.at(index);
				} catch (std::out_of_range ex) {
					// log error message
				}
				return node;
			}
		}
	}
}