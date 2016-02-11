#include "compoService.h"

CCompoService::CCompoService(CCompoSymbol* name = nullptr, std::vector<CCompoSymbol*> params = std::vector<CCompoSymbol*>(0), std::vector<CCompoNode*> body = std::vector<CCompoNode*>(0))
: CCompoNode(NodeTypeEnum::SERVICE), m_name(name), m_params(params), m_body(body)
{}

CCompoService::~CCompoService() {
    delete m_name;
    
    for (CCompoSymbol *symbol : m_params) {
        delete symbol;
    }
    
    for (CCompoNode *expr : m_body) {
        delete expr;
    }
}

void CCompoService::print(std::ostream& os) const {
    os << "\t";
    os << typeName(m_type) << " ";
    
    os << *m_name << " (";
    
    bool first = true;
    for (CCompoSymbol *symbol : m_params) {
        if (!first) {
            os << ", ";
            first = false;
        }
        os << *symbol;
    }
    
    os << ") {" << std::endl;
    os << "\t";
    os << "}" << std::endl;
}

CCompoSymbol * CCompoService::getName() const {
    return m_name;
}

std::vector<CCompoNode*> * CCompoService::getBody() {
    return &m_body;
}

void CCompoService::setBody(std::vector<CCompoNode*> body) {
    m_body = body;
}

std::vector<CCompoSymbol*> * CCompoService::getParams() {
    return &m_params;
}

void CCompoService::setParam(CCompoSymbol* param) {
    m_params.push_back(param);
}