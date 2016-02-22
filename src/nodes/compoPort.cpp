#include "compoPort.h"

namespace compo {
    
    CCompoPort::CCompoPort(CCompoSymbol* name, bool atomic)
    :   CCompoNode(NodeTypeEnum::PORT),
        m_name(name), m_atomic(atomic)
    {}
    
    CCompoPort::CCompoPort(const CCompoPort& p)
    : CCompoNode(p.m_nodeType),
      m_name(new CCompoSymbol(*p.m_name)),
      m_atomic(p.m_atomic)
    {}

    CCompoPort::CCompoPort(CCompoPort&& p) noexcept
    : CCompoNode(std::move(p.m_nodeType)),
      m_name(std::move(p.m_name)),
      m_atomic(std::move(p.m_atomic))
    {}
    
    CCompoPort& CCompoPort::operator =(const CCompoPort& p) {
        if (&p != this) {
            this->m_nodeType = p.m_nodeType;
            this->m_atomic = p.m_atomic;
            this->m_name = new CCompoSymbol(*p.m_name);
        }
        return *this;
    }
    
    CCompoPort& CCompoPort::operator =(CCompoPort&& p) noexcept {
        if (&p != this) {
            this->m_nodeType = std::move(p.m_nodeType);
            this->m_atomic = std::move(p.m_atomic);
            this->m_name = std::move(p.m_name);
        }
        return *this;
    }
    
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