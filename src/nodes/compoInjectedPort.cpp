#include "compoInjectedPort.h"

namespace compo {
    
    CCompoInjectedPort::CCompoInjectedPort( CCompoSymbol* name,
                                            bool atomic,
                                            CCompoSymbol* injectedWith  )
    :   CCompoNode(NodeTypeEnum::INJECTED_PORT),
        CCompoPort(name, atomic),
        m_injectedWith(injectedWith)
    {}

    CCompoInjectedPort::CCompoInjectedPort(const CCompoInjectedPort& other)
    : CCompoNode(other),
      CCompoPort(other),
      m_injectedWith(new CCompoSymbol(*other.m_injectedWith))
    {}

    CCompoInjectedPort::CCompoInjectedPort(CCompoInjectedPort&& other) noexcept
    : CCompoNode(std::move(other)),
      CCompoPort(std::move(other)),
      m_injectedWith(other.m_injectedWith)
    {
        other.m_injectedWith = nullptr;
    }
    
    CCompoInjectedPort& CCompoInjectedPort::operator =(const CCompoInjectedPort& other) {
        if (&other != this) {
            this->m_nodeType = other.m_nodeType;
            this->m_atomic = other.m_atomic;
            this->m_name = new CCompoSymbol(*other.m_name);
            this->m_injectedWith = new CCompoSymbol(*other.m_injectedWith);
        }
        return *this;
    }
    
    CCompoInjectedPort& CCompoInjectedPort::operator =(CCompoInjectedPort&& other) noexcept {
        if (&other != this) {
            this->m_nodeType = std::move(other.m_nodeType);
            this->m_atomic = std::move(other.m_atomic);
            this->m_name = other.m_name;
            other.m_name = nullptr;
            this->m_injectedWith = other.m_injectedWith;
            other.m_injectedWith = nullptr;
        }
        return *this;
    }
    
    CCompoNode* CCompoInjectedPort::clone() const {
        return new CCompoInjectedPort(*this);
    }
    
    CCompoInjectedPort::~CCompoInjectedPort() {
        delete m_injectedWith;
    }

    void CCompoInjectedPort::print(std::ostream& outstream) const {
        outstream << "\t";
        outstream << *m_name << " : { }";
    }

    std::string CCompoInjectedPort::getInjectedWith() const {
        if (m_injectedWith) {
            return m_injectedWith->getStringValue();
        }
        return "";
    }
}