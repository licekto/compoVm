#include "compoProvision.h"

CCompoProvision::CCompoProvision(bool externally = false, PORT_VECTOR ports = PORT_VECTOR(0))
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
    PRINT_TAB;
    if (m_externally) {
        os << "externally ";
    }

    os << "provides {" << std::endl;
    
    for (CCompoPort *port : m_ports) {
        PRINT_TAB;
        os << *port << std::endl;
    }
    
    PRINT_TAB;
    os << "}" << std::endl;
}