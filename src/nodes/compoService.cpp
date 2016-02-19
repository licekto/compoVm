#include "compoService.h"

CCompoService::CCompoService(   CCompoSymbol* name,
                                std::vector<CCompoSymbol*> params,
                                std::vector<CCompoNode*> body,
                                std::vector<CCompoNode*> temporaries    )
:   CCompoNode(NodeTypeEnum::SERVICE),
    CCompoAbstractService(name, params, body),
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