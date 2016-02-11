#include "compoProvision.h"

CCompoProvision::CCompoProvision(bool externally = false, std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0))
: CCompoNode(NodeTypeEnum::PROVISION), m_externally(externally), m_ports(ports)
{}

CCompoProvision::~CCompoProvision() {
    for (CCompoPort *port : m_ports) {
        delete port;
    }
}

void CCompoProvision::print(std::ostream& os) const {
    if (!m_toString) {
        os << typeName(m_type) << " ";
    }
    os << "\t";
    if (m_externally) {
        os << "externally ";
    }

    os << "provides {" << std::endl;
    
    for (CCompoPort *port : m_ports) {
        os << "\t";;
        os << *port << std::endl;
    }
    
    os << "\t";;
    os << "}" << std::endl;
}

bool CCompoProvision::isExternal() {
    return m_externally;
}

std::vector<CCompoPort*> * CCompoProvision::getPorts() {
    return &m_ports;
}