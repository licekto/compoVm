#include "compoInjectedPort.h"

CCompoInjectedPort::CCompoInjectedPort(CCompoSymbol* name, bool atomic, CCompoSymbol* injectedWith)
:   CCompoNode(NodeTypeEnum::INJECTED_NODE),
    CCompoPort(name, atomic),
    m_injectedWith(injectedWith)
{}

CCompoInjectedPort::~CCompoInjectedPort() {
    delete m_injectedWith;
}

void CCompoInjectedPort::print(std::ostream& os) const {
    os << "\t";
    os << *m_name << " : { }";
}
