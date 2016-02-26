#include "nodes/compoNodes/compoRequirement.h"

namespace compo {
    
    CCompoRequirement::CCompoRequirement(   visibilityType type,
                                            const std::vector<CCompoPort*>& ports)
    :   CCompoNode(NodeTypeEnum::REQUIREMENT),
        CCompoAbstractReqProv(type, ports)
    {}
    
    CCompoRequirement::CCompoRequirement(const CCompoRequirement& other)
    : CCompoNode(other),
      CCompoAbstractReqProv(other)
    {}

    
    CCompoRequirement::CCompoRequirement(CCompoRequirement&& other) noexcept
    : CCompoNode(std::move(other)),
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
    
    CCompoNode * CCompoRequirement::clone() const {
        return new CCompoRequirement(*this);
    }
    
    CCompoRequirement::~CCompoRequirement() {
    }

}