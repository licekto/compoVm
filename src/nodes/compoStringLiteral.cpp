#include "compoStringLiteral.h"

namespace compo {
    CCompoStringLiteral::CCompoStringLiteral(const std::string& val)
    : CCompoNode(NodeTypeEnum::INTEGER_LITERAL),
      m_stringValue(val) 
    {}
    
    CCompoStringLiteral::CCompoStringLiteral(const CCompoStringLiteral& other)
    : CCompoNode(other),
      m_stringValue(other.m_stringValue)
    {}

    CCompoStringLiteral::CCompoStringLiteral(CCompoStringLiteral&& other) noexcept
    : CCompoNode(std::move(other)),
      m_stringValue(std::move(other.m_stringValue))
    {}
    
    CCompoStringLiteral& CCompoStringLiteral::operator =(const CCompoStringLiteral& other) {
        if (&other != this) {
            m_nodeType = other.m_nodeType;
            m_stringValue = other.m_stringValue;
        }
        return *this;
    }
    
    CCompoStringLiteral& CCompoStringLiteral::operator =(CCompoStringLiteral&& other) noexcept {
        if (&other != this) {
            m_nodeType = std::move(other.m_nodeType);
            m_stringValue = std::move(other.m_stringValue);
        }
        return *this;
    }
    
    CCompoNode * CCompoStringLiteral::clone() const {
        return new CCompoStringLiteral(*this);
    }
    
    CCompoStringLiteral::~CCompoStringLiteral()
    {}
    
    void CCompoStringLiteral::print(std::ostream& outStr) const {
        outStr << m_stringValue;
    }
    
    std::string CCompoStringLiteral::getValue() const {
        return m_stringValue;
    }
}