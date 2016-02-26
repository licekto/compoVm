#include "nodes/compoNodes/compoConstraint.h"

namespace compo {
    
    CCompoConstraint::CCompoConstraint( CCompoSymbol* name,
                                        const std::vector<CCompoSymbol*>& params,
                                        const std::vector<CCompoNode*>& body)
    :   CCompoNode(NodeTypeEnum::CONSTRAINT),
        CCompoAbstractServConstr(name, params, body)
    {}
    
    CCompoConstraint::CCompoConstraint(const CCompoConstraint& other)
    : CCompoNode(other),
      CCompoAbstractServConstr(other)
    {
        *this = other;
    }

    CCompoConstraint::CCompoConstraint(CCompoConstraint&& other) noexcept
    : CCompoNode(std::move(other)),
      CCompoAbstractServConstr(std::move(other))
    {
        *this = std::move(other);
    }
    
    CCompoConstraint& CCompoConstraint::operator =(const CCompoConstraint& other) {
        if (&other != this) {
        }
        return *this;
    }
    
    CCompoConstraint& CCompoConstraint::operator =(CCompoConstraint&& other) noexcept {
        if (&other != this) {
        }
        return *this;
    }
    
    CCompoNode * CCompoConstraint::clone() const {
        return new CCompoConstraint(*this);
    }
    
    CCompoConstraint::~CCompoConstraint() {}

}