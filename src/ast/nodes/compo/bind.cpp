#include "ast/nodes/compo/bind.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CBind::CBind(std::shared_ptr<ast::nodes::compo::CPortAddress> portIdentification1,
			             std::shared_ptr<ast::nodes::compo::CPortAddress> portIdentification2)
				:   CNode(types::nodeType::CONNECTION),
				    m_portIdentification1(portIdentification1), m_portIdentification2(portIdentification2) {
			}

			std::shared_ptr<ast::nodes::compo::CPortAddress> CBind::getSourcePortIdentification() const {
				return m_portIdentification1;
			}

			std::shared_ptr<ast::nodes::compo::CPortAddress> CBind::getDestinationPortIdentification() const {
				return m_portIdentification2;
			}
		}
	}
}