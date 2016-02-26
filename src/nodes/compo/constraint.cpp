#include "nodes/compo/constraint.h"

namespace nodes {

    namespace compo {
    
        CConstraint::CConstraint( procedural::CSymbol* name,
                                            const std::vector<procedural::CSymbol*>& params,
                                            const std::vector<CNode*>& body)
        :   CNode(types::nodeType::CONSTRAINT),
            CAbstractServConstr(name, params, body)
        {}

        CConstraint::CConstraint(const CConstraint& other)
        : CNode(other),
          CAbstractServConstr(other)
        {
            *this = other;
        }

        CConstraint::CConstraint(CConstraint&& other) noexcept
        : CNode(std::move(other)),
          CAbstractServConstr(std::move(other))
        {
            *this = std::move(other);
        }

        CConstraint& CConstraint::operator =(const CConstraint& other) {
            if (&other != this) {
            }
            return *this;
        }

        CConstraint& CConstraint::operator =(CConstraint&& other) noexcept {
            if (&other != this) {
            }
            return *this;
        }

        CNode * CConstraint::clone() const {
            return new CConstraint(*this);
        }

        CConstraint::~CConstraint() {}

    }
}