#include "nodes/procedural/ifStatement.h"

namespace nodes {

	namespace procedural {

		CIfStatement::CIfStatement(std::shared_ptr<nodes::procedural::CAbstractExpression> condition,
		                           std::shared_ptr<nodes::procedural::CCompoundBody> ifBody,
		                           std::shared_ptr<nodes::procedural::CCompoundBody> elseBody)
			:   CNode(types::nodeType::IF),
			    m_condition(condition),
			    m_ifBody(ifBody),
			    m_elseBody(elseBody) {
		}

		void CIfStatement::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << "for (";
			outstream << m_condition << "; ";
			outstream << *m_ifBody << std::endl;
			outstream << "}" << std::endl;
		}

		std::shared_ptr<nodes::procedural::CCompoundBody> CIfStatement::getIfBody() const {
			return m_ifBody;
		}

		std::shared_ptr<nodes::procedural::CCompoundBody> CIfStatement::getElseBody() const {
			return m_elseBody;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CIfStatement::getCondition() const {
			return m_condition;
		}

	}

}