#include "nodes/proceduralNodes/compoParens.h"

namespace compo {
    CCompoParens::CCompoParens(CCompoNode *expr)
    : CCompoNode(NodeTypeEnum::PARENS),
      m_expression(expr)
    {}
    
    CCompoParens::CCompoParens(const CCompoParens& other)
    : CCompoNode(other),
      m_expression(other.m_expression)
    {}

    CCompoParens::CCompoParens(CCompoParens&& other) noexcept
    : CCompoNode(std::move(other)),
      m_expression(std::move(other.m_expression))
    {}
    
    CCompoParens& CCompoParens::operator =(const CCompoParens& other) {
        if (&other != this) {
            m_nodeType = other.m_nodeType;
            m_expression = other.m_expression;
        }
        return *this;
    }
    
    CCompoParens& CCompoParens::operator =(CCompoParens&& other) noexcept {
        if (&other != this) {
            m_nodeType = std::move(other.m_nodeType);
            m_expression = std::move(other.m_expression);
        }
        return *this;
    }
    
    CCompoNode * CCompoParens::clone() const {
        return new CCompoParens(*this);
    }
    
    CCompoParens::~CCompoParens()
    {}
    
    void CCompoParens::print(std::ostream& outStr) const {
        outStr << m_expression;
    }
    
    CCompoNode * CCompoParens::getExpression() const {
        return m_expression;
    }
}