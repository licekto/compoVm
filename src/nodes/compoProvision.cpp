#include "compoProvision.h"

CCompoProvision::CCompoProvision(visibilityType type = visibilityType::EXTERNAL, std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0))
:   CCompoNode(NodeTypeEnum::PROVISION),
    CCompoAbstractReqProv(type, ports)
{}

CCompoProvision::~CCompoProvision() {
}