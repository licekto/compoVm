#include "nodes/procedural/forStatement.h"
#include "nodes/procedural/whileStatement.h"

namespace nodes {

	namespace procedural {

		CWhileStatement::CWhileStatement(   std::shared_ptr<nodes::procedural::CAbstractExpression> cond,
		                                    std::shared_ptr<nodes::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::WHILE),
			    m_condition(cond),
			    m_body(body) {
		}

		void CWhileStatement::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << "while (";
			outstream << m_condition << ") {" << std::endl;
			outstream << *m_body << std::endl;
			outstream << "}" << std::endl;
		}

		std::shared_ptr<nodes::procedural::CCompoundBody> CWhileStatement::getBody() const {
			return m_body;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CWhileStatement::getCondition() const {
			return m_condition;
		}

	}

}