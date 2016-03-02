#include "nodes/compo/abstractReqProv.h"

namespace nodes {

	namespace compo {

		CAbstractReqProv::CAbstractReqProv(types::visibilityType type,
		                                   const std::vector<std::shared_ptr<nodes::compo::CPort>>& ports,
                                                   bool universality)
			: CNode(types::nodeType::PROVISION),
                          m_visibilityType(type),
                          m_ports(ports),
                          m_universality(universality) {
		}

		void CAbstractReqProv::print(std::ostream& outstream) const {
			outstream << "\t";
			if (m_visibilityType == types::visibilityType::EXTERNAL) {
				outstream << "externally ";
			} else if (m_visibilityType == types::visibilityType::INTERNAL) {
				outstream << "internally ";
			}

			outstream << "provides {" << std::endl;

			for (std::shared_ptr<nodes::compo::CPort> port : m_ports) {
				outstream << "\t";;
				outstream << *port << std::endl;
			}

			outstream << "\t";;
			outstream << "}" << std::endl;
		}

		types::visibilityType CAbstractReqProv::getVisibilityType() const {
			return m_visibilityType;
		}

		size_t CAbstractReqProv::getNumberOfPorts() const {
			return m_ports.size();
		}

		std::shared_ptr<nodes::compo::CPort> CAbstractReqProv::getPortAt(unsigned int index) const {
			std::shared_ptr<nodes::compo::CPort> port = nullptr;
			try {
				port = m_ports.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return port;
		}
                
                bool CAbstractReqProv::getUniversality() const {
                    return m_universality;
                }

	}

}