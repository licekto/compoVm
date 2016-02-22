#include "compoRequirement.h"

namespace compo {
    
    CCompoRequirement::CCompoRequirement(   visibilityType type,
                                            const std::vector<CCompoPort*>& ports)
    :   CCompoNode(NodeTypeEnum::REQUIREMENT),
        CCompoAbstractReqProv(type, ports)
    {}
    
    CCompoRequirement::CCompoRequirement(const CCompoRequirement& other)
    : CCompoNode(other.m_nodeType),
      CCompoAbstractReqProv(other)
    {}

    
    CCompoRequirement::CCompoRequirement(CCompoRequirement&& other) noexcept
    : CCompoNode(std::move(other.m_nodeType)),
      CCompoAbstractReqProv(std::move(other))
    {}
    
    CCompoRequirement& CCompoRequirement::operator =(const CCompoRequirement& other) {
        if (&other != this) {
            *this = other;
        }
        return *this;
    }

    CCompoRequirement& CCompoRequirement::operator =(CCompoRequirement&& other) noexcept {
        if (&other != this) {
            *this = std::move(other);
        }
        return *this;
    }
    
    CCompoRequirement::~CCompoRequirement() {
    }

}