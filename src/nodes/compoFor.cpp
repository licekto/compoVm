#include "compoFor.h"

CCompoFor::CCompoFor(   CCompoNode* startCond,
                        CCompoNode* endCond,
                        CCompoNode* step,
                        std::vector<CCompoNode*> body)
:   CCompoNode(NodeTypeEnum::FOR),
    m_startCondition(startCond),
    m_endCondition(endCond),
    m_step(step),
    m_body(body) // TODO: move semantics could be used here to move vector
{}

CCompoFor::~CCompoFor() {
    delete m_startCondition;
    delete m_endCondition;
    delete m_step;
    for (CCompoNode *expr : m_body) {
        delete expr;
    }
}

void CCompoFor::print(std::ostream& outstream) const {
    outstream << "\t";
    outstream << "for (";
    outstream << m_startCondition << "; ";
    outstream << m_endCondition << "; ";
    outstream << m_step << ") {";
    if (m_body.size() != 0) {
        for (CCompoNode *expr : m_body) {
            outstream << "\t\t";
            outstream << *expr;
        }
    }
    outstream << "}" << std::endl;
}

std::vector<CCompoNode*> * CCompoFor::getBody() const {
    return const_cast<std::vector<CCompoNode*> *>(&m_body); // yuck
}

CCompoNode * CCompoFor::getStartCond() const {
    return const_cast<CCompoNode *>(m_startCondition);
}

CCompoNode * CCompoFor::getEndCond() const {
    return const_cast<CCompoNode *>(m_endCondition);
}

CCompoNode * CCompoFor::getStep() const  {
    return const_cast<CCompoNode *>(m_step);
}