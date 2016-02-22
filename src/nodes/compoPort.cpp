#include "compoPort.h"

namespace compo {
    
    CCompoPort::CCompoPort(CCompoSymbol* name, bool atomic)
    :   CCompoNode(NodeTypeEnum::PORT),
        m_name(name), m_atomic(atomic)
    {}
    
    CCompoPort::CCompoPort(const CCompoPort& other)
    : CCompoNode(other),
      m_name(new CCompoSymbol(*other.m_name)),
      m_atomic(other.m_atomic)
    {}

    CCompoPort::CCompoPort(CCompoPort&& other) noexcept
    : CCompoNode(std::move(other)),
      m_name(new CCompoSymbol(std::move(*other.m_name))),
      m_atomic(std::move(other.m_atomic))
    {}
    
    CCompoPort& CCompoPort::operator =(const CCompoPort& other) {
        if (&other != this) {
            this->m_nodeType = other.m_nodeType;
            this->m_atomic = other.m_atomic;
            this->m_name = new CCompoSymbol(*other.m_name);
        }
        return *this;
    }
    
    CCompoPort& CCompoPort::operator =(CCompoPort&& other) noexcept {
        if (&other != this) {
            this->m_nodeType = std::move(other.m_nodeType);
            this->m_atomic = std::move(other.m_atomic);
            this->m_name = std::move(other.m_name);
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
    
    bool CCompoPort::getAtomic() const {
        return m_atomic;
    }

}