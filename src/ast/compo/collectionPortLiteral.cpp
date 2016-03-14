#include "ast/compo/collectionPortLiteral.h"

namespace ast {

	namespace compo {

		CCollectionPortLiteral::CCollectionPortLiteral(std::shared_ptr<ast::procedural::CSymbol> portName,
		        std::shared_ptr<ast::procedural::CAbstractExpression> indexExpression)
			:   CNode(types::nodeType::COLLECTION_PORT),
			    m_portName(portName),
			    m_indexExpression(indexExpression) {
		}

		void CCollectionPortLiteral::print(std::ostream& outstream) const {
			outstream << "&" << *m_portName << std::endl;
		}

		std::shared_ptr<ast::procedural::CSymbol> CCollectionPortLiteral::getPortName() const {
			return m_portName;
		}

		std::shared_ptr<ast::procedural::CAbstractExpression> CCollectionPortLiteral::getIndexExpression() const {
			return m_indexExpression;
		}
	}

}