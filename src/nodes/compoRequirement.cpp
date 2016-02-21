#include "compoRequirement.h"

namespace compo {
    
    CCompoRequirement::CCompoRequirement(   visibilityType type,
                                            const std::vector<CCompoPort*>& ports)
    :   CCompoNode(NodeTypeEnum::REQUIREMENT),
        CCompoAbstractReqProv(type, ports)
    {}

    CCompoRequirement::~CCompoRequirement() {
    }

}