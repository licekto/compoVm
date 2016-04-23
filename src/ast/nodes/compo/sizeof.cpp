#include "ast/nodes/compo/sizeof.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CSizeof::CSizeof(std::shared_ptr<ast::nodes::procedural::CSymbol> parameter)
				:   CNode(types::nodeType::SIZEOF),
				    m_parameter(parameter) {
			}

			void CSizeof::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CSizeof::getParamName() const {
				return m_parameter;
			}
		}
	}
}