#include "nodes/compoNodes/compoDescriptor.h"

namespace compo {
    
    CCompoDescriptor::CCompoDescriptor( CCompoSymbol *name,
                                        CCompoSymbol *extends,
                                        const std::vector<CCompoNode*>& body)
    : CCompoNode(NodeTypeEnum::DESCRIPTOR), m_name(name), m_extends(extends), m_body(body)
    {}
    
    CCompoDescriptor::CCompoDescriptor(const CCompoDescriptor& other)
    : CCompoNode(other),
      m_name(new CCompoSymbol(*other.m_name)),
      m_extends(new CCompoSymbol(*other.m_extends))
    {
        *this = other;
    }

    CCompoDescriptor::CCompoDescriptor(CCompoDescriptor&& other) noexcept
    : CCompoNode(std::move(other)),
      m_name(other.m_name),
      m_extends(other.m_extends),
      m_body(std::move(other.m_body))
    {
        other.m_name = nullptr;
        other.m_extends = nullptr;
    }
    
    CCompoDescriptor& CCompoDescriptor::operator =(const CCompoDescriptor& other) {
        if (&other != this) {
            m_nodeType = other.m_nodeType;
            m_name = new CCompoSymbol(*other.m_name);
            m_extends = new CCompoSymbol(*other.m_extends);
            for (CCompoNode *node : other.m_body) {
                this->m_body.push_back(node->clone());
            }
        }
        return *this;
    }
    
    CCompoDescriptor& CCompoDescriptor::operator =(CCompoDescriptor&& other) noexcept {
        if (&other != this) {
            m_nodeType = std::move(other.m_nodeType);
            m_name = other.m_name;
            other.m_name = nullptr;
            m_extends = other.m_extends;
            other.m_extends = nullptr;
            m_body = std::move(other.m_body);
        }
        return *this;
    }
    
    CCompoNode * CCompoDescriptor::clone() const {
        return new CCompoDescriptor(*this);
    }
    
    CCompoDescriptor::~CCompoDescriptor() {
        delete m_name;
        delete m_extends;
        for (CCompoNode *expr : m_body) {
            delete expr;
        }
    }

    void CCompoDescriptor::print(std::ostream& outstream) const {
        outstream << typeName(m_nodeType) << " ";
        if (m_name) {
            outstream << *m_name << " ";
        }
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

    std::string CCompoDescriptor::getName() const {
        if (m_name) {
            return m_name->getStringValue();
        }
        return "";
    }

    void CCompoDescriptor::setExtends(CCompoSymbol* extends) {
        m_extends = extends;
    }

    std::string CCompoDescriptor::getExtends() const {
        if (m_extends) {
            return m_extends->getStringValue();
        }
        return "";
    }

    size_t CCompoDescriptor::getBodySize() const {
        return m_body.size();
    }
    
    CCompoNode * CCompoDescriptor::getBodyNodeAt(int index) const {
        CCompoNode * node = nullptr;
        try {
            node = m_body.at(index);
        } catch (std::out_of_range ex) {
            // log error message
        }
        return node;
    }
    
}