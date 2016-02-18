#include "compoAbstractReqProv.h"

CCompoAbstractReqProv::CCompoAbstractReqProv(visibilityType type = visibilityType::EXTERNAL, std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0))
: CCompoNode(NodeTypeEnum::PROVISION), m_intExtType(type), m_ports(ports)
{}

CCompoAbstractReqProv::~CCompoAbstractReqProv() {
    for (CCompoPort *port : m_ports) {
        delete port;
    }
}

void CCompoAbstractReqProv::print(std::ostream& os) const {
    os << "\t";
    if (m_intExtType == visibilityType::EXTERNAL) {
        os << "externally ";
    } else if (m_intExtType == visibilityType::INTERNAL) {
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

visibilityType CCompoAbstractReqProv::getVisibilityType() {
    return m_intExtType;
}

std::vector<CCompoPort*> * CCompoAbstractReqProv::getPorts() const {
    return const_cast<std::vector<CCompoPort*> *>(&m_ports);    // yuck
}