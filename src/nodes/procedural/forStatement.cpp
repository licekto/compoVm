#include "nodes/procedural/forStatement.h"

namespace nodes {

	namespace procedural {

		CForStatement::CForStatement(   std::shared_ptr<nodes::procedural::CAssignmentExpression> startCond,
		                                std::shared_ptr<nodes::procedural::CAbstractExpression> endCond,
		                                std::shared_ptr<nodes::procedural::CAbstractExpression> step,
		                                std::shared_ptr<nodes::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::FOR),
			    m_startCondition(startCond),
			    m_endCondition(endCond),
			    m_step(step),
			    m_body(body) {
		}

		void CForStatement::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << "for (";
			outstream << m_startCondition << "; ";
			outstream << m_endCondition << "; ";
			outstream << m_step << ") {";
			outstream << *m_body << std::endl;
			outstream << "}" << std::endl;
		}

		std::shared_ptr<nodes::procedural::CCompoundBody> CForStatement::getBody() const {
			return m_body;
		}

		std::shared_ptr<nodes::procedural::CAssignmentExpression> CForStatement::getStartCond() const {
			return m_startCondition;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CForStatement::getEndCond() const {
			return m_endCondition;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CForStatement::getStep() const  {
			return m_step;
		}

	}

}