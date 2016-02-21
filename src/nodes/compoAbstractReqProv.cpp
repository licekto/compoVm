#include "compoAbstractReqProv.h"

namespace compo {
    
    CCompoAbstractReqProv::CCompoAbstractReqProv(   visibilityType type,
                                                    const std::vector<CCompoPort*>& ports)
    : CCompoNode(NodeTypeEnum::PROVISION), m_visibilityType(type), m_ports(ports)
    {}

    CCompoAbstractReqProv::CCompoAbstractReqProv(const CCompoAbstractReqProv& rp)
    : CCompoNode(rp.m_nodeType), m_visibilityType(rp.m_visibilityType) {
        *this = rp;
    }
    
    CCompoAbstractReqProv::CCompoAbstractReqProv(CCompoAbstractReqProv&& rp) noexcept
    : CCompoNode(std::move(rp.m_nodeType)),
      m_visibilityType(std::move(rp.m_visibilityType))
    {
        this->m_ports = std::move(rp.m_ports);
    }
    
    CCompoAbstractReqProv& CCompoAbstractReqProv::operator =(const CCompoAbstractReqProv& rp) {
        if (&rp != this) {
            this->m_nodeType = rp.m_nodeType;
            this->m_visibilityType = rp.m_visibilityType;
            this->m_ports.clear();

            for (CCompoPort *port : rp.m_ports) {
                this->m_ports.push_back(new CCompoPort(*port));     // Create whole new instance of port
            }
        }
        
        return *this;
    }
    
    CCompoAbstractReqProv& CCompoAbstractReqProv::operator =(CCompoAbstractReqProv&& rp) noexcept {
        this->m_nodeType = rp.m_nodeType;
        this->m_visibilityType = rp.m_visibilityType;
        this->m_ports.clear();
        
        this->m_ports = std::move(rp.m_ports);
        
        return *this;
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