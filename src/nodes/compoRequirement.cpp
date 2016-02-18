#include "compoRequirement.h"

CCompoRequirement::CCompoRequirement(intExtType type = intExtType::PLAIN, std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0))
:   CCompoNode(NodeTypeEnum::REQUIREMENT),
    CCompoAbstractReqProv(type, ports)
{}

CCompoRequirement::~CCompoRequirement() {
}