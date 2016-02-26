#include "nodes/compo/abstractReqProv.h"

namespace nodes {

    namespace compo {

        CAbstractReqProv::CAbstractReqProv(   types::visibilityType type,
                                                        const std::vector<CPort*>& ports)
        : CNode(types::NodeTypeEnum::PROVISION), m_visibilityType(type), m_ports(ports)
        {}

        CAbstractReqProv::CAbstractReqProv(const CAbstractReqProv& other)
        : CNode(other), m_visibilityType(other.m_visibilityType) {
            *this = other;
        }

        CAbstractReqProv::CAbstractReqProv(CAbstractReqProv&& other) noexcept
        : CNode(std::move(other)),
          m_visibilityType(std::move(other.m_visibilityType)),
          m_ports(std::move(other.m_ports))
        {}

        CAbstractReqProv& CAbstractReqProv::operator =(const CAbstractReqProv& other) {
            if (&other != this) {
                this->m_nodeType = other.m_nodeType;
                this->m_visibilityType = other.m_visibilityType;
                this->m_ports.clear();

                for (CPort *port : other.m_ports) {
                    this->m_ports.push_back(new CPort(*port));     // Create whole new instance of ports
                }
            }

            return *this;
        }

        CAbstractReqProv& CAbstractReqProv::operator =(CAbstractReqProv&& other) noexcept {
            this->m_nodeType = other.m_nodeType;
            this->m_visibilityType = other.m_visibilityType;
            this->m_ports.clear();

            this->m_ports = std::move(other.m_ports);

            return *this;
        }

        CNode * CAbstractReqProv::clone() const {
            return new CAbstractReqProv(*this);
        }

        CAbstractReqProv::~CAbstractReqProv() {
            for (CPort *port : m_ports) {
                delete port;
            }
        }

        void CAbstractReqProv::print(std::ostream& outstream) const {
            outstream << "\t";
            if (m_visibilityType == types::visibilityType::EXTERNAL) {
                outstream << "externally ";
            } else if (m_visibilityType == types::visibilityType::INTERNAL) {
                outstream << "internally ";
            }

            outstream << "provides {" << std::endl;

            for (CPort *port : m_ports) {
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

        CPort * CAbstractReqProv::getPortAt(unsigned int index) const {
            CPort * port = nullptr;
            try {
                port = m_ports.at(index);
            } catch (std::out_of_range ex) {
                // log error message
            }
            return port;
        }

    }

}