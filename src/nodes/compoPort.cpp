#include "compoPort.h"

CCompoPort::CCompoPort(CCompoSymbol* name = nullptr, bool atomic = false)
: CCompoNode(NodeTypeEnum::PORT), m_name(name), m_atomic(atomic)
{}

CCompoPort::~CCompoPort() {
    delete m_name;
}

void CCompoPort::print(std::ostream& os) const {
    if (!m_toString) {
        os << typeName(m_type) << " ";
    }
    
    PRINT_TAB;
    os << *m_name << " : { }";
}

CCompoSymbol * CCompoPort::getName() const {
    return m_name;
}