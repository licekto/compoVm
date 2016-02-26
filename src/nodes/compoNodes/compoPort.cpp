#include "nodes/compoNodes/compoPort.h"

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
      m_name(other.m_name),
      m_atomic(std::move(other.m_atomic))
    {
        other.m_name = nullptr;
    }
    
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
            this->m_name = other.m_name;
            other.m_name = nullptr;
        }
        return *this;
    }
    
    CCompoNode* CCompoPort::clone() const {
        return new CCompoPort(*this);
    }

    
    CCompoPort::~CCompoPort() {
        delete m_name;
    }

    void CCompoPort::print(std::ostream& outstream) const {
        if (m_name) {
            outstream << "\t";
            outstream << *m_name << " : { }";
        }
    }

    std::string CCompoPort::getName() const {
        if (m_name) {
            return m_name->getStringValue();
        }
        return "";
    }
    
    bool CCompoPort::getAtomic() const {
        return m_atomic;
    }

}