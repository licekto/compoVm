#include "compoService.h"

CCompoService::CCompoService(   CCompoSymbol* name,
                                const std::vector<CCompoSymbol*>& params,
                                const std::vector<CCompoNode*>& body,
                                const std::vector<CCompoNode*>& temporaries    )
:   CCompoNode(NodeTypeEnum::SERVICE),
    CCompoAbstractServConstr(name, params, body),
    m_temporaries(temporaries)
{}

CCompoService::~CCompoService() {
    for (CCompoNode * node : m_temporaries) {
        delete node;
    }
}

std::vector<CCompoNode*> * CCompoService::getTemporaries() const {
    return const_cast<std::vector<CCompoNode*> *>(&m_temporaries);
}