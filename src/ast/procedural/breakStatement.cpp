#include "ast/procedural/breakStatement.h"

namespace ast {

	namespace procedural {

		CBreakStatement::CBreakStatement()
			:   CNode(types::nodeType::BREAK) {
		}

		void CBreakStatement::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << "break;";
		}
	}

}