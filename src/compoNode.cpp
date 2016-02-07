#include "compoNode.h"

std::map<NodeTypeEnum, const char *> typeNames = {
    {NodeTypeEnum::END, "End"},
    {NodeTypeEnum::DESCRIPTOR, "Descriptor"},
    {NodeTypeEnum::SYMBOL, "Symbol"},
    {NodeTypeEnum::SERVICE, "Service"}
};

const char * typeName(NodeTypeEnum type) {
    return typeNames[type];
}

/*----------------------------------------------------------------------------*/

CCompoNode::CCompoNode(NodeTypeEnum type = NodeTypeEnum::END) : m_type(type), m_toString(true) {}

std::ostream& operator << (std::ostream& os, const CCompoNode& node) {
    node.print(os);
    return os;
}

/*----------------------------------------------------------------------------*/

CCompoSymbol::CCompoSymbol(const std::string& name) : CCompoNode(NodeTypeEnum::SYMBOL), m_name(name) {}

void CCompoSymbol::print(std::ostream& os) const {
    if (!m_toString) {
        os << typeName(m_type) << " ";
    }
    os << m_name;
}

std::string CCompoSymbol::getName() const {
    return m_name;
}

/*----------------------------------------------------------------------------*/

CCompoDescriptor::CCompoDescriptor(CCompoSymbol *name = nullptr, CCompoSymbol *extends = nullptr, CCompoNode* body = nullptr)
: CCompoNode(NodeTypeEnum::DESCRIPTOR), m_name(name), m_extends(extends), m_body(body)
{}

CCompoDescriptor::~CCompoDescriptor() {
    delete m_name;
    delete m_body;
}

void CCompoDescriptor::print(std::ostream& os) const {
    os << typeName(m_type) << " ";
    os << *m_name << " ";
    if (m_extends) {
        os << "extends " << *m_extends << std::endl;
    }
    os << "{";
    
    if (m_body) {
        
    }
    
    os << "}";
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
/*----------------------------------------------------------------------------*/


CCompoService::CCompoService(CCompoSymbol* name = nullptr, SYMBOL_VECTOR params = SYMBOL_VECTOR(0), CCompoNode* body = nullptr)
: CCompoNode(NodeTypeEnum::SERVICE), m_name(name), m_params(params), m_body(body)
{}

CCompoService::~CCompoService() {
    delete m_name;
    
    for (CCompoSymbol *symbol : m_params) {
        delete symbol;
    }
    
    delete m_body;
}

void CCompoService::print(std::ostream& os) const {
    if (!m_toString) {
        os << typeName(m_type) << " ";
    }
    
    os << *m_name << " (";
    
    bool first = true;
    for (CCompoSymbol *symbol : m_params) {
        if (!first) {
            os << ", ";
            first = false;
        }
        os << *symbol;
    }
    
    os << ") {" << *m_body << std::endl << "}";
}

CCompoSymbol * CCompoService::getName() const {
    return m_name;
}

CCompoNode * CCompoService::getBody() const {
    return m_body;
}

void CCompoService::setBody(CCompoNode* body) {
    m_body = body;
}

SYMBOL_VECTOR * CCompoService::getParams() {
    return &m_params;
}

void CCompoService::setParam(CCompoSymbol* param) {
    m_params.push_back(param);
}