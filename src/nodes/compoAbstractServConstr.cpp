#include "compoAbstractServConstr.h"

CCompoAbstractServConstr::CCompoAbstractServConstr(   CCompoSymbol* name,
                                                const std::vector<CCompoSymbol*>& params,
                                                const std::vector<CCompoNode*>& body)
: CCompoNode(NodeTypeEnum::SERVICE), m_name(name), m_params(params), m_body(body)
{}

CCompoAbstractServConstr::~CCompoAbstractServConstr() {
    delete m_name;
    
    for (CCompoSymbol *symbol : m_params) {
        delete symbol;
    }
    
    for (CCompoNode *expr : m_body) {
        delete expr;
    }
}

void CCompoAbstractServConstr::print(std::ostream& outstream) const {
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

CCompoSymbol * CCompoAbstractServConstr::getName() const {
    return m_name;
}

std::vector<CCompoNode*> * CCompoAbstractServConstr::getBody() const {
    return const_cast<std::vector<CCompoNode*> *>(&m_body);
}

void CCompoAbstractServConstr::setBody(const std::vector<CCompoNode*>& body) {
    m_body = body;
}

std::vector<CCompoSymbol*> * CCompoAbstractServConstr::getParams() const {
    return const_cast<std::vector<CCompoSymbol*> *>(&m_params);
}

void CCompoAbstractServConstr::setParam(CCompoSymbol* param) {
    m_params.push_back(param);
}