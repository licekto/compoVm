#include "nodes/procedural/parens.h"

namespace nodes {

    namespace procedural {
        
        CParens::CParens(CNode *expr)
        : CNode(types::NodeTypeEnum::PARENS),
          m_expression(expr)
        {}

        CParens::CParens(const CParens& other)
        : CNode(other),
          m_expression(other.m_expression)
        {}

        CParens::CParens(CParens&& other) noexcept
        : CNode(std::move(other)),
          m_expression(std::move(other.m_expression))
        {}

        CParens& CParens::operator =(const CParens& other) {
            if (&other != this) {
                m_nodeType = other.m_nodeType;
                m_expression = other.m_expression;
            }
            return *this;
        }

        CParens& CParens::operator =(CParens&& other) noexcept {
            if (&other != this) {
                m_nodeType = std::move(other.m_nodeType);
                m_expression = std::move(other.m_expression);
            }
            return *this;
        }

        CNode * CParens::clone() const {
            return new CParens(*this);
        }

        CParens::~CParens()
        {}

        void CParens::print(std::ostream& outStr) const {
            outStr << m_expression;
        }

        CNode * CParens::getExpression() const {
            return m_expression;
        }
    }
    
}