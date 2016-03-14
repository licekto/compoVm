#include "ast/compo/bind.h"

namespace ast {

	namespace compo {

		CBind::CBind(std::shared_ptr<ast::compo::CPortAddress> portIdentification1,
		             std::shared_ptr<ast::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::CONNECTION),
			    m_portIdentification1(portIdentification1), m_portIdentification2(portIdentification2) {
		}

		void CBind::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << *m_portIdentification1 << " : { }";
		}

		std::shared_ptr<ast::compo::CPortAddress> CBind::getPortIdentification1() const {
			return m_portIdentification1;
		}

		std::shared_ptr<ast::compo::CPortAddress> CBind::getPortIdentification2() const {
			return m_portIdentification2;
		}
	}

}