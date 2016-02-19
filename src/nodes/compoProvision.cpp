#include "compoProvision.h"

CCompoProvision::CCompoProvision(visibilityType type, std::vector<CCompoPort*> ports)
:   CCompoNode(NodeTypeEnum::PROVISION),
    CCompoAbstractReqProv(type, ports)
{}

CCompoProvision::~CCompoProvision() {
}