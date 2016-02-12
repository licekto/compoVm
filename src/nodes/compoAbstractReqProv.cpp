#include "compoAbstractReqProv.h"

CCompoAbstractReqProv::CCompoAbstractReqProv(intExtType type = intExtType::PLAIN, std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0))
: CCompoNode(NodeTypeEnum::PROVISION), m_intExtType(type), m_ports(ports)
{}

CCompoAbstractReqProv::~CCompoAbstractReqProv() {
    for (CCompoPort *port : m_ports) {
        delete port;
    }
}

void CCompoAbstractReqProv::print(std::ostream& os) const {
    if (!m_toString) {
        os << typeName(m_type) << " ";
    }
    os << "\t";
    if (m_intExtType == intExtType::EXTERNAL) {
        os << "externally ";
    } else if (m_intExtType == intExtType::INTERNAL) {
        os << "internally ";
    }

    os << "provides {" << std::endl;
    
    for (CCompoPort *port : m_ports) {
        os << "\t";;
        os << *port << std::endl;
    }
    
    os << "\t";;
    os << "}" << std::endl;
}

intExtType CCompoAbstractReqProv::getType() {
    return m_intExtType;
}

std::vector<CCompoPort*> * CCompoAbstractReqProv::getPorts() {
    return &m_ports;
}