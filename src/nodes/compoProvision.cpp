#include "compoProvision.h"

namespace compo {
    
    CCompoProvision::CCompoProvision(   visibilityType type,
                                        const std::vector<CCompoPort*>& ports)
    :   CCompoNode(NodeTypeEnum::PROVISION),
        CCompoAbstractReqProv(type, ports)
    {}

    CCompoProvision::CCompoProvision(const CCompoProvision& other)
    : CCompoNode(other),
      CCompoAbstractReqProv(other)
    {}

    
    CCompoProvision::CCompoProvision(CCompoProvision&& other) noexcept
    : CCompoNode(std::move(other)),
      CCompoAbstractReqProv(std::move(other))
    {}
    
    CCompoProvision& CCompoProvision::operator =(const CCompoProvision& other) {
        if (&other != this) {
            *this = other;
        }
        return *this;
    }

    CCompoProvision& CCompoProvision::operator =(CCompoProvision&& other) noexcept {
        if (&other != this) {
            *this = std::move(other);
        }
        return *this;
    }
    
    CCompoProvision::~CCompoProvision() {
    }

}