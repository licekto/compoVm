#include "ast/nodes/program.h"

namespace ast {

	namespace nodes {

		CProgram::CProgram()
			: CNode(ast::nodes::types::nodeType::PROGRAM),
			  m_rootNodes(std::vector<std::shared_ptr<CNode>>(0)) {

		}

		void CProgram::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}


		void CProgram::addNode(std::shared_ptr<CNode> node) {
			m_rootNodes.push_back(node);
		}

		size_t CProgram::getNodesSize() const {
			return m_rootNodes.size();
		}

		std::shared_ptr<CNode> CProgram::getNodeAt(size_t i) const {
			std::shared_ptr<CNode> node = nullptr;
			try {
				node = m_rootNodes.at(i);
			} catch (const std::out_of_range& ex) {
				// log error message
			}
			return node;
		}
	}
}