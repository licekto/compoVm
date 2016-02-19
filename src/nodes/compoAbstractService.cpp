#include "compoAbstractService.h"

CCompoAbstractService::CCompoAbstractService(   CCompoSymbol* name,
                                                std::vector<CCompoSymbol*> params,
                                                std::vector<CCompoNode*> body)
: CCompoNode(NodeTypeEnum::SERVICE), m_name(name), m_params(params), m_body(body)
{}

CCompoAbstractService::~CCompoAbstractService() {
    delete m_name;
    
    for (CCompoSymbol *symbol : m_params) {
        delete symbol;
    }
    
    for (CCompoNode *expr : m_body) {
        delete expr;
    }
}

void CCompoAbstractService::print(std::ostream& outstream) const {
    outstream << "\t";
    outstream << typeName(m_type) << " ";
    
    outstream << *m_name << " (";
    
    bool first = true;
    for (CCompoSymbol *symbol : m_params) {
        if (!first) {
            outstream << ", ";
            first = false;
        }
        outstream << *symbol;
    }
    
    outstream << ") {" << std::endl;
    outstream << "\t";
    outstream << "}" << std::endl;
}

CCompoSymbol * CCompoAbstractService::getName() const {
    return m_name;
}

std::vector<CCompoNode*> * CCompoAbstractService::getBody() const {
    return const_cast<std::vector<CCompoNode*> *>(&m_body);
}

void CCompoAbstractService::setBody(std::vector<CCompoNode*> body) {
    m_body = body;
}

std::vector<CCompoSymbol*> * CCompoAbstractService::getParams() const {
    return const_cast<std::vector<CCompoSymbol*> *>(&m_params);
}

void CCompoAbstractService::setParam(CCompoSymbol* param) {
    m_params.push_back(param);
}