#include "ast/nodes/compo/abstractReqProv.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		CAbstractReqProv::CAbstractReqProv(types::visibilityType type,
		                                   const std::vector<std::shared_ptr<ast::nodes::compo::CPort>>& ports)
			: m_visibilityType(type),
			  m_ports(ports) {
		}

		void CAbstractReqProv::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		types::visibilityType CAbstractReqProv::getVisibilityType() const {
			return m_visibilityType;
		}

		size_t CAbstractReqProv::getNumberOfPorts() const {
			return m_ports.size();
		}

		std::shared_ptr<ast::nodes::compo::CPort> CAbstractReqProv::getPortAt(unsigned int index) const {
			std::shared_ptr<ast::nodes::compo::CPort> port = nullptr;
			try {
				port = m_ports.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return port;
		}

	}
        
    }

}