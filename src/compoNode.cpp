#include "compoNode.h"

const char *typeNames[] = {
    "End",
    "Descriptor",
    "Symbol"
};

const char * typeName(NodeTypeEnum type) {
    return typeNames[type];
}

/*----------------------------------------------------------------------------*/

#define PRINT_TYPE                  \
do {                                \
    os << typeName(m_type) << " ";   \
}                                   \
while (0)

CCompoNode::CCompoNode(NodeTypeEnum type = NodeTypeEnum::END) : m_type(type), m_toString(true) {}

std::ostream& operator << (std::ostream& os, const CCompoNode& node) {
    node.print(os);
    return os;
}

/*----------------------------------------------------------------------------*/

CCompoSymbol::CCompoSymbol(const std::string& name) : CCompoNode(NodeTypeEnum::SYMBOL), m_name(name) {}

std::string CCompoSymbol::getName() const {
    return m_name;
}

void CCompoSymbol::print(std::ostream& os) const {
    if (!m_toString) {
        PRINT_TYPE;
    }
    os << m_name;
}

/*----------------------------------------------------------------------------*/

CCompoDescriptor::CCompoDescriptor(CCompoSymbol *name = nullptr, CCompoSymbol *extends = nullptr, CCompoNode* body = nullptr)
: CCompoNode(NodeTypeEnum::DESCRIPTOR), m_name(name), m_extends(extends), m_body(body)
{}

CCompoDescriptor::~CCompoDescriptor() {
    delete m_name;
    delete m_body;
}

CCompoSymbol * CCompoDescriptor::getName() const {
    return m_name;
}

void CCompoDescriptor::print(std::ostream& os) const {
    PRINT_TYPE;
    os << *m_name << " ";
    if (m_extends) {
        os << "extends " << *m_extends << std::endl;
    }
    os << "{";
    
    if (m_body) {
        
    }
    
    os << "}";
}

void CCompoDescriptor::setExtends(CCompoSymbol* extends) {
    m_extends = extends;
}

CCompoSymbol * CCompoDescriptor::getExtends() const {
    return m_extends;
}

/*----------------------------------------------------------------------------*/