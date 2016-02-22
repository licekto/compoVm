#include "compoAssignment.h"

namespace compo {
    
    CCompoAssignment::CCompoAssignment(CCompoSymbol * variable, CCompoNode * rVal)
    :   CCompoNode(NodeTypeEnum::ASSIGNMENT),
        m_variable(variable), m_rValue(rVal)
    {}
    
    CCompoAssignment::CCompoAssignment(const CCompoAssignment& other)
    : CCompoNode(other),
      m_variable(new CCompoSymbol(*other.m_variable))
      //m_rValue(new CCompoNode(*other.m_rValue))
    {}
    
    CCompoAssignment::CCompoAssignment(CCompoAssignment&& other) noexcept
    : CCompoNode(std::move(other)),
      m_variable(new CCompoSymbol(std::move(*other.m_variable)))
      //m_rValue(new CCompoNode(std::move(*other.m_rValue)))
    {}

    CCompoAssignment& CCompoAssignment::operator =(const CCompoAssignment& other) {
        if (&other != this) {
            this->m_nodeType = other.m_nodeType;
            this->m_variable = new CCompoSymbol(*other.m_variable);
            //this->m_rValue = new CCompoNode(*other.m_rValue);
        }
        
        return *this;
    }
    
    CCompoAssignment& CCompoAssignment::operator =(CCompoAssignment&& other) noexcept {
        if (&other != this) {
            this->m_nodeType = std::move(other.m_nodeType);
            this->m_variable = new CCompoSymbol(std::move(*other.m_variable));
            //this->m_rValue = new CCompoNode(std::move(*other.m_rValue));
        }
        
        return *this;
    }
    
    CCompoNode * CCompoAssignment::clone() const {
        return new CCompoAssignment(*this);
    }
    
    CCompoAssignment::~CCompoAssignment() {
        delete m_variable;
        delete m_rValue;
    }

    void CCompoAssignment::print(std::ostream& outstream) const {
        outstream << m_variable << " = " << m_rValue << ";" << std::endl;
    }

    CCompoSymbol * CCompoAssignment::getVariable() const {
        return const_cast<CCompoSymbol *>(m_variable);
    }

    CCompoNode * CCompoAssignment::getRValue() const {
        return const_cast<CCompoNode *>(m_rValue);
    }

}