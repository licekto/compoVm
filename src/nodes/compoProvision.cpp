#include "compoProvision.h"

CCompoProvision::CCompoProvision(intExtType type = intExtType::PLAIN, std::vector<CCompoPort*> ports = std::vector<CCompoPort*>(0))
:   CCompoNode(NodeTypeEnum::PROVISION),
    CCompoAbstractReqProv(type, ports)
{}

CCompoProvision::~CCompoProvision() {
}