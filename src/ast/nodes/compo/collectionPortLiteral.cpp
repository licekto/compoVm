#include "ast/nodes/compo/collectionPortLiteral.h"

namespace ast {
    
    namespace nodes {

	namespace compo {

		CCollectionPortLiteral::CCollectionPortLiteral(std::shared_ptr<ast::nodes::procedural::CSymbol> portName,
		        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> indexExpression)
			:   CNode(types::nodeType::COLLECTION_PORT),
			    m_portName(portName),
			    m_indexExpression(indexExpression) {
		}

		void CCollectionPortLiteral::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::nodes::procedural::CSymbol> CCollectionPortLiteral::getPortName() const {
			return m_portName;
		}

		std::shared_ptr<ast::nodes::procedural::CAbstractExpression> CCollectionPortLiteral::getIndexExpression() const {
			return m_indexExpression;
		}
	}
    }
}