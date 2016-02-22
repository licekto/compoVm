#include "compoArchitecture.h"

namespace compo {
    
    CCompoArchitecture::CCompoArchitecture()
    : CCompoNode(NodeTypeEnum::ARCHITECTURE)
    {}

    CCompoArchitecture::CCompoArchitecture(const CCompoArchitecture& other)
    : CCompoNode(other) {
    }
    
    CCompoArchitecture::CCompoArchitecture(CCompoArchitecture&& other) noexcept
    : CCompoNode(std::move(other))
    {}
    
    CCompoArchitecture& CCompoArchitecture::operator =(const CCompoArchitecture& other) {
        if (&other != this) {
        }
        
        return *this;
    }
    
    CCompoArchitecture& CCompoArchitecture::operator =(CCompoArchitecture&& other) noexcept {
        if (&other != this) {
        }
        return *this;
    }
    
    CCompoNode * CCompoArchitecture::clone() const {
        return new CCompoArchitecture(*this);
    }
    
    CCompoArchitecture::~CCompoArchitecture() {}

    void CCompoArchitecture::print(std::ostream& outStr) const {
        outStr << "\t";
        outStr << "architecture {}";
        
        outStr << std::endl;
    }
}