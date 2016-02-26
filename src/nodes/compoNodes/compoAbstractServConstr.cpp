#include "nodes/compoNodes/compoAbstractServConstr.h"

namespace compo {
    
    CCompoAbstractServConstr::CCompoAbstractServConstr(   CCompoSymbol* name,
                                                    const std::vector<CCompoSymbol*>& params,
                                                    const std::vector<CCompoNode*>& body)
    : CCompoNode(NodeTypeEnum::SERVICE), m_name(name), m_params(params), m_body(body)
    {}

    CCompoAbstractServConstr::CCompoAbstractServConstr(const CCompoAbstractServConstr& other)
    : CCompoNode(other)
    {
        *this = other;
    }
    
    CCompoAbstractServConstr::CCompoAbstractServConstr(CCompoAbstractServConstr&& other) noexcept
    : CCompoNode(std::move(other)),
      m_name(other.m_name),
      m_params(std::move(other.m_params)),
      m_body(std::move(other.m_body))
    {
        other.m_name = nullptr;
    }
    
    CCompoAbstractServConstr& CCompoAbstractServConstr::operator =(const CCompoAbstractServConstr& other) {
        if (&other != this) {
            this->m_nodeType = other.m_nodeType;
            
            this->m_name = new CCompoSymbol(*other.m_name);
            
            for (CCompoSymbol *symbol : other.m_params) {
                this->m_params.push_back(new CCompoSymbol(*symbol));
            }
            
            for (CCompoNode *node : other.m_body) {
                this->m_body.push_back(node->clone());
            }
        }
        
        return *this;
    }
    
    CCompoAbstractServConstr& CCompoAbstractServConstr::operator =(CCompoAbstractServConstr&& other) noexcept {
        if (&other != this) {
            this->m_nodeType = std::move(other.m_nodeType);
            this->m_name = other.m_name;
            other.m_name = nullptr;
            this->m_params = std::move(other.m_params);
            this->m_body = std::move(other.m_body);
        }
        return *this;
    }
    
    CCompoNode * CCompoAbstractServConstr::clone() const {
        return new CCompoAbstractServConstr(*this);
    }
    
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
        outstream << typeName(m_nodeType) << " ";

        if (m_name) {
            outstream << *m_name << " (";
        }

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

    std::string CCompoAbstractServConstr::getName() const {
        if (m_name) {
            return m_name->getStringValue();
        }
        return "";
    }

    size_t CCompoAbstractServConstr::getBodySize() const {
        return m_body.size();
    }
    
    CCompoNode * CCompoAbstractServConstr::getBodyNodeAt(int index) const {
        CCompoNode * node = nullptr;
        try {
            node = m_body.at(index);
        } catch (std::out_of_range ex) {
            // log error message
        }
        return node;
    }

    void CCompoAbstractServConstr::setBodyNode(CCompoNode* bodyNode) {
        m_body.push_back(bodyNode);
    }

    size_t CCompoAbstractServConstr::getParamsSize() const {
        return m_params.size();
    }
    
    CCompoSymbol * CCompoAbstractServConstr::getParamAt(int index) const {
        CCompoSymbol * param = nullptr;
        try {
            param = m_params.at(index);
        } catch (std::out_of_range ex) {
            // log error message
        }
        return param;
    }

    void CCompoAbstractServConstr::setParam(CCompoSymbol* param) {
        m_params.push_back(param);
    }

}