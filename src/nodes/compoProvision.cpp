#include "compoProvision.h"

namespace compo {
    
    CCompoProvision::CCompoProvision(   visibilityType type,
                                        const std::vector<CCompoPort*>& ports)
    :   CCompoNode(NodeTypeEnum::PROVISION),
        CCompoAbstractReqProv(type, ports)
    {}

    CCompoProvision::~CCompoProvision() {
    }

}