#include "compoConstraint.h"

CCompoConstraint::CCompoConstraint(CCompoSymbol* name = nullptr, std::vector<CCompoSymbol*> params = std::vector<CCompoSymbol*>(0), std::vector<CCompoNode*> body = std::vector<CCompoNode*>(0))
:   CCompoNode(NodeTypeEnum::CONSTRAINT),
    CCompoAbstractService(name, params, body) {}

CCompoConstraint::~CCompoConstraint() {}