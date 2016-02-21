#include "compoAssignment.h"

namespace compo {
    
    CCompoAssignment::CCompoAssignment(CCompoSymbol * variable, CCompoNode * rVal)
    :   CCompoNode(NodeTypeEnum::ASSIGNMENT),
        m_variable(variable), m_rValue(rVal)
    {}

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