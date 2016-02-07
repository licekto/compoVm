#include "compoNode.h"

std::map<NodeTypeEnum, const char *> typeNames = {
    {NodeTypeEnum::END, "End"},
    {NodeTypeEnum::DESCRIPTOR, "Descriptor"},
    {NodeTypeEnum::SYMBOL, "Symbol"},
    {NodeTypeEnum::SERVICE, "service"},
    {NodeTypeEnum::PORT, "port"},
    {NodeTypeEnum::PROVISION, "provides"}
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
/*----------------------------------------------------------------------------*/

CCompoService::CCompoService(CCompoSymbol* name = nullptr, SYMBOL_VECTOR params = SYMBOL_VECTOR(0), NODE_VECTOR body = NODE_VECTOR(0))
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

NODE_VECTOR * CCompoService::getBody() {
    return &m_body;
}

void CCompoService::setBody(NODE_VECTOR body) {
    m_body = body;
}

SYMBOL_VECTOR * CCompoService::getParams() {
    return &m_params;
}

void CCompoService::setParam(CCompoSymbol* param) {
    m_params.push_back(param);
}

/*----------------------------------------------------------------------------*/

CCompoPort::CCompoPort(CCompoSymbol* name = nullptr, bool atomic = false)
: CCompoNode(NodeTypeEnum::PORT), m_name(name), m_atomic(atomic)
{}

CCompoPort::~CCompoPort() {
    delete m_name;
}

void CCompoPort::print(std::ostream& os) const {
    if (!m_toString) {
        os << typeName(m_type) << " ";
    }
    
    PRINT_TAB;
    os << *m_name << " : { }";
}

CCompoSymbol * CCompoPort::getName() const {
    return m_name;
}
/*----------------------------------------------------------------------------*/


CCompoProvision::CCompoProvision(bool externally = false, PORT_VECTOR ports = PORT_VECTOR(0))
: CCompoNode(NodeTypeEnum::PROVISION), m_externally(externally), m_ports(ports)
{}

CCompoProvision::~CCompoProvision() {
    for (CCompoPort *port : m_ports) {
        delete port;
    }
}

void CCompoProvision::print(std::ostream& os) const {
    if (!m_toString) {
        os << typeName(m_type) << " ";
    }
    PRINT_TAB;
    if (m_externally) {
        os << "externally ";
    }

    os << "provides {" << std::endl;
    
    for (CCompoPort *port : m_ports) {
        PRINT_TAB;
        os << *port << std::endl;
    }
    
    PRINT_TAB;
    os << "}" << std::endl;
}