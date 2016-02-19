#include "compoConstraint.h"

CCompoConstraint::CCompoConstraint( CCompoSymbol* name,
                                    std::vector<CCompoSymbol*> params,
                                    std::vector<CCompoNode*> body)
:   CCompoNode(NodeTypeEnum::CONSTRAINT),
    CCompoAbstractService(name, params, body) {}

CCompoConstraint::~CCompoConstraint() {}