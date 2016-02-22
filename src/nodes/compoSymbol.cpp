#include "compoSymbol.h"
#include "compoService.h"

namespace compo {
    
    CCompoSymbol::CCompoSymbol(const std::string& name)
    :   CCompoNode(NodeTypeEnum::SYMBOL),
        m_name(name)
    {}
    
    CCompoSymbol::CCompoSymbol(const CCompoSymbol& other)
    : CCompoNode(other),
      m_name(other.m_name)
    {}
    
    CCompoSymbol::CCompoSymbol(CCompoSymbol&& other) noexcept
    : CCompoNode(std::move(other)),
      m_name(std::move(other.m_name))
    {
        other.m_name.clear();
    }
    
    CCompoSymbol& CCompoSymbol::operator= (const CCompoSymbol& other) {
         if (&other != this) {
            this->m_nodeType = other.m_nodeType;
            this->m_name = other.m_name;
         }
         return *this;
    }
    
    CCompoSymbol& CCompoSymbol::operator= (CCompoSymbol&& other) noexcept {
         if (&other != this) {
            this->m_nodeType = std::move(other.m_nodeType);
            this->m_name = std::move(other.m_name);
            other.m_name.clear();
         }
         return *this;
    }
    
    CCompoNode * CCompoSymbol::clone() const {
        return new CCompoSymbol(*this);
    }
    
    CCompoSymbol::~CCompoSymbol() {
    }

    void CCompoSymbol::print(std::ostream& outstream) const {
        outstream << m_name;
    }

    std::string CCompoSymbol::getStringValue() const {
        return m_name;
    }

}