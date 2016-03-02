#include "nodes/procedural/breakStatement.h"

namespace nodes {

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