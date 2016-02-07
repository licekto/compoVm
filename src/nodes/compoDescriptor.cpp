#include "compoDescriptor.h"

CCompoDescriptor::CCompoDescriptor(CCompoSymbol *name = nullptr, CCompoSymbol *extends = nullptr, NODE_VECTOR body = NODE_VECTOR(0))
: CCompoNode(NodeTypeEnum::DESCRIPTOR), m_name(name), m_extends(extends), m_body(body)
{}

CCompoDescriptor::~CCompoDescriptor() {
    delete m_name;
    for (CCompoNode *expr : m_body) {
        delete expr;
    }
}

void CCompoDescriptor::print(std::ostream& os) const {
    os << typeName(m_type) << " ";
    os << *m_name << " ";
    if (m_extends) {
        os << "extends " << *m_extends;
    }
    os << " {" << std::endl;
    
    if (m_body.size() != 0) {
        for (CCompoNode *expr : m_body) {
            os << *expr;
        }
    }
    
    os << "}" << std::endl;
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