#include "ast/program.h"

namespace ast {

	CProgram::CProgram()
		: CNode(ast::types::nodeType::PROGRAM),
		  m_rootNodes(std::vector<std::shared_ptr<ast::CNode>>(0)) {

	}

	void CProgram::accept(ast::visitors::CAbstractVisitor* visitor) {
		visitor->visit(this);
	}


	void CProgram::addNode(std::shared_ptr<ast::CNode> node) {
		m_rootNodes.push_back(node);
	}

	size_t CProgram::getNodesSize() const {
		return m_rootNodes.size();
	}

	std::shared_ptr<ast::CNode> CProgram::getNodeAt(size_t i) const {
		std::shared_ptr<ast::CNode> node = nullptr;
		try {
			node = m_rootNodes.at(i);
		} catch (std::out_of_range ex) {
			// log error message
		}
		return node;
	}

}