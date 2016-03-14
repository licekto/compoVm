#include "ast/procedural/continueStatement.h"

namespace ast {

	namespace procedural {

		CContinueStatement::CContinueStatement()
			:   CNode(types::nodeType::CONTINUE) {
		}

		void CContinueStatement::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << "continue;";
		}
	}

}