#include "nodes/procedural/for.h"

namespace nodes {

	namespace procedural {

		CFor::CFor(   std::shared_ptr<nodes::procedural::CAssignmentExpression> startCond,
		              std::shared_ptr<nodes::procedural::CAbstractExpression> endCond,
		              std::shared_ptr<nodes::procedural::CAbstractExpression> step,
		              const std::vector<std::shared_ptr<nodes::CNode>>& body)
			:   CNode(types::nodeType::FOR),
			    m_startCondition(startCond),
			    m_endCondition(endCond),
			    m_step(step),
			    m_body(body) { // TODO: move semantics could be used here to move vector
		}

		void CFor::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << "for (";
			outstream << m_startCondition << "; ";
			outstream << m_endCondition << "; ";
			outstream << m_step << ") {";
			if (m_body.size() != 0) {
				for (std::shared_ptr<nodes::CNode> expr : m_body) {
					outstream << "\t\t";
					outstream << *expr;
				}
			}
			outstream << "}" << std::endl;
		}

		std::shared_ptr<nodes::CNode> CFor::getBodyNodeAt(int index) const {
			std::shared_ptr<nodes::CNode> node = nullptr;
			try {
				node = m_body.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

		std::shared_ptr<nodes::procedural::CAssignmentExpression> CFor::getStartCond() const {
			return m_startCondition;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CFor::getEndCond() const {
			return m_endCondition;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CFor::getStep() const  {
			return m_step;
		}

	}

}