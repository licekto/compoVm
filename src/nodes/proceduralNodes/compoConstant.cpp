#include "nodes/proceduralNodes/compoConstant.h"

namespace compo {
    CCompoConstant::CCompoConstant(i32 val)
    : CCompoNode(NodeTypeEnum::CONSTANT),
      m_intValue(val) 
    {}
    
    CCompoConstant::CCompoConstant(const CCompoConstant& other)
    : CCompoNode(other),
      m_intValue(other.m_intValue)
    {}

    CCompoConstant::CCompoConstant(CCompoConstant&& other) noexcept
    : CCompoNode(std::move(other)),
      m_intValue(std::move(other.m_intValue))
    {}
    
    CCompoConstant& CCompoConstant::operator =(const CCompoConstant& other) {
        if (&other != this) {
            m_nodeType = other.m_nodeType;
            m_intValue = other.m_intValue;
        }
        return *this;
    }
    
    CCompoConstant& CCompoConstant::operator =(CCompoConstant&& other) noexcept {
        if (&other != this) {
            m_nodeType = std::move(other.m_nodeType);
            m_intValue = std::move(other.m_intValue);
        }
        return *this;
    }
    
    CCompoNode * CCompoConstant::clone() const {
        return new CCompoConstant(*this);
    }
    
    CCompoConstant::~CCompoConstant()
    {}
    
    void CCompoConstant::print(std::ostream& outStr) const {
        outStr << m_intValue;
    }
    
    i32 CCompoConstant::getValue() const {
        return m_intValue;
    }
}