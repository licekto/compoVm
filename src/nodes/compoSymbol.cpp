#include "compoSymbol.h"

CCompoSymbol::CCompoSymbol(const std::string& name) : CCompoNode(NodeTypeEnum::SYMBOL), m_name(name) {}

void CCompoSymbol::print(std::ostream& os) const {
    os << m_name;
}

std::string CCompoSymbol::getName() const {
    return m_name;
}