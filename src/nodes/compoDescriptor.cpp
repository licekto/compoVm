#include "compoDescriptor.h"

CCompoDescriptor::CCompoDescriptor( CCompoSymbol *name,
                                    CCompoSymbol *extends,
                                    const std::vector<CCompoNode*>& body)
: CCompoNode(NodeTypeEnum::DESCRIPTOR), m_name(name), m_extends(extends), m_body(body)
{}

CCompoDescriptor::~CCompoDescriptor() {
    delete m_name;
    for (CCompoNode *expr : m_body) {
        delete expr;
    }
}

void CCompoDescriptor::print(std::ostream& outstream) const {
    outstream << typeName(m_type) << " ";
    outstream << *m_name << " ";
    if (m_extends) {
        outstream << "extends " << *m_extends;
    }
    outstream << " {" << std::endl;
    
    if (m_body.size() != 0) {
        for (CCompoNode *expr : m_body) {
            outstream << *expr;
        }
    }
    
    outstream << "}" << std::endl;
}

CCompoSymbol * CCompoDescriptor::getName() const {
    return m_name;
}

void CCompoDescriptor::setExtends(CCompoSymbol* extends) {
    m_extends = extends;
}

CCompoSymbol * CCompoDescriptor::getExtends() const {
    return m_extends;
}

std::vector<CCompoNode*> * CCompoDescriptor::getBody() const {
    return const_cast<std::vector<CCompoNode*> *>(&m_body); // yuck
}