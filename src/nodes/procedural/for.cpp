#include "nodes/procedural/for.h"

namespace nodes {

    namespace procedural {
    
        CFor::CFor(   CNode* startCond,
                                CNode* endCond,
                                CNode* step,
                                const std::vector<CNode*>& body)
        :   CNode(types::nodeTypeEnum::FOR),
            m_startCondition(startCond),
            m_endCondition(endCond),
            m_step(step),
            m_body(body) // TODO: move semantics could be used here to move vector
        {}
        
        CFor::CFor(const CFor& other)
        : CNode(other)
          //m_startCondition(new CCompoNode(other.m_startCondition),
        {}

        CFor::CFor(CFor&& other) noexcept
        : CNode(std::move(other))
        {}

        CFor& CFor::operator = (const CFor& other) {
            if (&other != this) {

            }
            return *this;
        }

        CFor& CFor::operator = (CFor&& other) noexcept {
            if (&other != this) {

            }
            return *this;
        }

        CNode * CFor::clone() const {
            return new CFor(*this);
        }

        CFor::~CFor() {
            delete m_startCondition;
            delete m_endCondition;
            delete m_step;
            for (CNode *expr : m_body) {
                delete expr;
            }
        }

        void CFor::print(std::ostream& outstream) const {
            outstream << "\t";
            outstream << "for (";
            outstream << m_startCondition << "; ";
            outstream << m_endCondition << "; ";
            outstream << m_step << ") {";
            if (m_body.size() != 0) {
                for (CNode *expr : m_body) {
                    outstream << "\t\t";
                    outstream << *expr;
                }
            }
            outstream << "}" << std::endl;
        }

        CNode * CFor::getBodyNodeAt(int index) const {
            CNode * node = nullptr;
            try {
                node = m_body.at(index);
            } catch (std::out_of_range ex) {
                // log error message
            }
            return node;
        }

        CNode * CFor::getStartCond() const {
            return const_cast<CNode *>(m_startCondition);
        }

        CNode * CFor::getEndCond() const {
            return const_cast<CNode *>(m_endCondition);
        }

        CNode * CFor::getStep() const  {
            return const_cast<CNode *>(m_step);
        }

    }
    
}