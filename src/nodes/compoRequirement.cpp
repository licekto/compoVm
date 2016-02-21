#include "compoRequirement.h"

namespace compo {
    
    CCompoRequirement::CCompoRequirement(   visibilityType type,
                                            const std::vector<CCompoPort*>& ports)
    :   CCompoNode(NodeTypeEnum::REQUIREMENT),
        CCompoAbstractReqProv(type, ports)
    {}
    
    CCompoRequirement::CCompoRequirement(const CCompoRequirement& other)
    : CCompoNode(req.m_nodeType),
      CCompoAbstractReqProv(req)
    {}

    
    CCompoRequirement::CCompoRequirement(CCompoRequirement&& other) noexcept
    : CCompoNode(std::move(req.m_nodeType)),
      CCompoAbstractReqProv(std::move(req))
    {}
    
    CCompoRequirement& CCompoRequirement::operator =(const CCompoRequirement& other) {
        if (&req != this) {
            *this = req;
        }
        return *this;
    }

    CCompoRequirement& CCompoRequirement::operator =(CCompoRequirement&& other) noexcept {
        if (&req != this) {
            *this = std::move(req);
        }
        return *this;
    }
    
    CCompoRequirement::~CCompoRequirement() {
    }

}