#include "compoPort.h"

namespace compo {
    
    CCompoPort::CCompoPort(CCompoSymbol* name, bool atomic)
    :   CCompoNode(NodeTypeEnum::PORT),
        m_name(name), m_atomic(atomic)
    {}

    CCompoPort::~CCompoPort() {
        delete m_name;
    }

    void CCompoPort::print(std::ostream& outstream) const {
        outstream << "\t";
        outstream << *m_name << " : { }";
    }

    CCompoSymbol * CCompoPort::getName() const {
        return m_name;
    }

}