#include "compoIntegerLiteral.h"
#include "compoInjectedPort.h"

namespace compo {
    CCompoIntegerLiteral::CCompoIntegerLiteral(i32 val)
    : CCompoNode(NodeTypeEnum::INTEGER_LITERAL),
      m_intValue(val) 
    {}
    
    CCompoIntegerLiteral::CCompoIntegerLiteral(const CCompoIntegerLiteral& other)
    : CCompoNode(other),
      m_intValue(other.m_intValue)
    {}

    CCompoIntegerLiteral::CCompoIntegerLiteral(CCompoIntegerLiteral&& other) noexcept
    : CCompoNode(std::move(other)),
      m_intValue(std::move(other.m_intValue))
    {}
    
    CCompoIntegerLiteral& CCompoIntegerLiteral::operator =(const CCompoIntegerLiteral& other) {
        if (&other != this) {
            m_nodeType = other.m_nodeType;
            m_intValue = other.m_intValue;
        }
        return *this;
    }
    
    CCompoIntegerLiteral& CCompoIntegerLiteral::operator =(CCompoIntegerLiteral&& other) noexcept {
        if (&other != this) {
            m_nodeType = std::move(other.m_nodeType);
            m_intValue = std::move(other.m_intValue);
        }
        return *this;
    }
    
    CCompoNode * CCompoIntegerLiteral::clone() const {
        return new CCompoIntegerLiteral(*this);
    }
    
    CCompoIntegerLiteral::~CCompoIntegerLiteral()
    {}
    
    void CCompoIntegerLiteral::print(std::ostream& outStr) const {
        outStr << m_intValue;
    }
    
    i32 CCompoIntegerLiteral::getValue() const {
        return m_intValue;
    }
}