#include "compoService.h"

CCompoService::CCompoService(CCompoSymbol* name = nullptr, std::vector<CCompoSymbol*> params = std::vector<CCompoSymbol*>(0), std::vector<CCompoNode*> body = std::vector<CCompoNode*>(0))
:   CCompoNode(NodeTypeEnum::SERVICE),
    CCompoAbstractService(name, params, body) {}

CCompoService::~CCompoService() {}