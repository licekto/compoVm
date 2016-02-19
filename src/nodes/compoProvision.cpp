#include "compoProvision.h"

CCompoProvision::CCompoProvision(   visibilityType type,
                                    const std::vector<CCompoPort*>& ports)
:   CCompoNode(NodeTypeEnum::PROVISION),
    CCompoAbstractReqProv(type, ports)
{}

CCompoProvision::~CCompoProvision() {
}