#include "compoRequirement.h"

CCompoRequirement::CCompoRequirement(visibilityType type = visibilityType::EXTERNAL, std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0))
:   CCompoNode(NodeTypeEnum::REQUIREMENT),
    CCompoAbstractReqProv(type, ports)
{}

CCompoRequirement::~CCompoRequirement() {
}