#include "nodes/compo/collectionPortLiteral.h"

namespace nodes {

	namespace compo {

		CCollectionPortLiteral::CCollectionPortLiteral(std::shared_ptr<nodes::procedural::CSymbol> portName,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> indexExpression)
			:   CNode(types::nodeType::COLLECTION_PORT),
			    m_portName(portName),
			    m_indexExpression(indexExpression) {
		}

		void CCollectionPortLiteral::print(std::ostream& outstream) const {
			outstream << "&" << *m_portName << std::endl;
		}

		std::shared_ptr<nodes::procedural::CSymbol> CCollectionPortLiteral::getPortName() const {
			return m_portName;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CCollectionPortLiteral::getIndexExpression() const {
			return m_indexExpression;
		}
	}

}