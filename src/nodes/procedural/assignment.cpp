#include "nodes/procedural/assignment.h"

namespace nodes {

    namespace procedural {
    
        CAssignment::CAssignment(CSymbol * variable, CNode * rVal)
        :   CNode(types::nodeType::ASSIGNMENT),
            m_variable(variable), m_rValue(rVal)
        {}

        CAssignment::CAssignment(const CAssignment& other)
        : CNode(other),
          m_variable(new CSymbol(*other.m_variable)),
          m_rValue(other.m_rValue->clone())
        {}

        CAssignment::CAssignment(CAssignment&& other) noexcept
        : CNode(std::move(other)),
          m_variable(new CSymbol(std::move(*other.m_variable))),
          m_rValue(other.m_rValue)
        {
            other.m_rValue = nullptr;
        }

        CAssignment& CAssignment::operator =(const CAssignment& other) {
            if (&other != this) {
                this->m_nodeType = other.m_nodeType;
                this->m_variable = new CSymbol(*other.m_variable);
                this->m_rValue = other.m_rValue->clone();
            }

            return *this;
        }

        CAssignment& CAssignment::operator =(CAssignment&& other) noexcept {
            if (&other != this) {
                this->m_nodeType = std::move(other.m_nodeType);
                this->m_variable = new CSymbol(std::move(*other.m_variable));
                this->m_rValue = other.m_rValue;
                other.m_rValue = nullptr;
            }

            return *this;
        }

        CNode * CAssignment::clone() const {
            return new CAssignment(*this);
        }

        CAssignment::~CAssignment() {
            delete m_variable;
            delete m_rValue;
        }

        void CAssignment::print(std::ostream& outstream) const {
            outstream << *m_variable << " := " << *m_rValue << ";" << std::endl;
        }

        CSymbol * CAssignment::getVariable() const {
            return m_variable;
        }

        CNode * CAssignment::getRValue() const {
            return m_rValue;
        }

    }
    
}