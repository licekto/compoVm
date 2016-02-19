#include "compoConstraint.h"

CCompoConstraint::CCompoConstraint( CCompoSymbol* name,
                                    const std::vector<CCompoSymbol*>& params,
                                    const std::vector<CCompoNode*>& body)
:   CCompoNode(NodeTypeEnum::CONSTRAINT),
    CCompoAbstractServConstr(name, params, body)
{}

CCompoConstraint::~CCompoConstraint() {}