#include "compoAbstractReqProv.h"

namespace compo {
    
    CCompoAbstractReqProv::CCompoAbstractReqProv(   visibilityType type,
                                                    const std::vector<CCompoPort*>& ports)
    : CCompoNode(NodeTypeEnum::PROVISION), m_visibilityType(type), m_ports(ports)
    {}

    CCompoAbstractReqProv::CCompoAbstractReqProv(const CCompoAbstractReqProv& other)
    : CCompoNode(other), m_visibilityType(other.m_visibilityType) {
        *this = other;
    }
    
    CCompoAbstractReqProv::CCompoAbstractReqProv(CCompoAbstractReqProv&& other) noexcept
    : CCompoNode(std::move(other)),
      m_visibilityType(std::move(other.m_visibilityType)),
      m_ports(std::move(other.m_ports))
    {}
    
    CCompoAbstractReqProv& CCompoAbstractReqProv::operator =(const CCompoAbstractReqProv& other) {
        if (&other != this) {
            this->m_nodeType = other.m_nodeType;
            this->m_visibilityType = other.m_visibilityType;
            this->m_ports.clear();

            for (CCompoPort *port : other.m_ports) {
                this->m_ports.push_back(new CCompoPort(*port));     // Create whole new instance of ports
            }
        }
        
        return *this;
    }
    
    CCompoAbstractReqProv& CCompoAbstractReqProv::operator =(CCompoAbstractReqProv&& other) noexcept {
        this->m_nodeType = other.m_nodeType;
        this->m_visibilityType = other.m_visibilityType;
        this->m_ports.clear();
        
        this->m_ports = std::move(other.m_ports);
        
        return *this;
    }
    
    CCompoNode * CCompoAbstractReqProv::clone() const {
        return new CCompoAbstractReqProv(*this);
    }
    
    CCompoAbstractReqProv::~CCompoAbstractReqProv() {
        for (CCompoPort *port : m_ports) {
            delete port;
        }
    }

    void CCompoAbstractReqProv::print(std::ostream& outstream) const {
        outstream << "\t";
        if (m_visibilityType == visibilityType::EXTERNAL) {
            outstream << "externally ";
        } else if (m_visibilityType == visibilityType::INTERNAL) {
            outstream << "internally ";
        }

        outstream << "provides {" << std::endl;

        for (CCompoPort *port : m_ports) {
            outstream << "\t";;
            outstream << *port << std::endl;
        }

        outstream << "\t";;
        outstream << "}" << std::endl;
    }

    visibilityType CCompoAbstractReqProv::getVisibilityType() {
        return m_visibilityType;
    }

    size_t CCompoAbstractReqProv::getNumberOfPorts() const {
        return m_ports.size();
    }
    
    CCompoPort * CCompoAbstractReqProv::getPortAt(unsigned int index) const {
        CCompoPort * port = nullptr;
        try {
            port = m_ports.at(index);
        } catch (std::out_of_range ex) {
            // log error message
        }
        return port;
    }

}