#include "compoFor.h"

namespace compo {
    
    CCompoFor::CCompoFor(   CCompoNode* startCond,
                            CCompoNode* endCond,
                            CCompoNode* step,
                            const std::vector<CCompoNode*>& body)
    :   CCompoNode(NodeTypeEnum::FOR),
        m_startCondition(startCond),
        m_endCondition(endCond),
        m_step(step),
        m_body(body) // TODO: move semantics could be used here to move vector
    {}
    CCompoFor::CCompoFor(const CCompoFor& other)
    : CCompoNode(other)
      //m_startCondition(new CCompoNode(other.m_startCondition),
    {}

    CCompoFor::CCompoFor(CCompoFor&& other) noexcept
    : CCompoNode(std::move(other))
    {}
    
    CCompoFor& CCompoFor::operator = (const CCompoFor& other) {
        if (&other != this) {
            
        }
        return *this;
    }
    
    CCompoFor& CCompoFor::operator = (CCompoFor&& other) noexcept {
        if (&other != this) {
            
        }
        return *this;
    }
    
    CCompoNode * CCompoFor::clone() const {
        return new CCompoFor(*this);
    }
    
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

    CCompoNode * CCompoFor::getBodyNodeAt(int index) const {
        CCompoNode * node = nullptr;
        try {
            node = m_body.at(index);
        } catch (std::out_of_range ex) {
            // log error message
        }
        return node;
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

}