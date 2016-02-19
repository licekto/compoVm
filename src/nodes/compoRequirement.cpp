#include "compoRequirement.h"

CCompoRequirement::CCompoRequirement(   visibilityType type,
                                        std::vector<CCompoPort*> ports)
:   CCompoNode(NodeTypeEnum::REQUIREMENT),
    CCompoAbstractReqProv(type, ports)
{}

CCompoRequirement::~CCompoRequirement() {
}