#include "compoSymbol.h"

namespace compo {
    
    CCompoSymbol::CCompoSymbol(const std::string& name)
    :   CCompoNode(NodeTypeEnum::SYMBOL),
        m_name(name)
    {}
    
    CCompoSymbol::~CCompoSymbol() {

    }

    void CCompoSymbol::print(std::ostream& outstream) const {
        outstream << m_name;
    }

    std::string CCompoSymbol::getStringValue() const {
        return m_name;
    }

}