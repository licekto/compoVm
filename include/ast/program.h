#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "node.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {
	/**
	 * \class CNode
	 * \brief Abstract base class for other nodes.
	 *
	 * Abstract base class of AST. Every node in AST is derived from this one.
	 */
	class CProgram : public CNode {
	  protected:

		/**< Vector of root nodes */
		std::vector<std::shared_ptr<ast::CNode>> m_rootNodes;

	  public:

		CProgram();

		/**
		* Accept method for visitor acceptation.
			 * @param visitor: Pointer to abstract visitor.
			 */
		virtual void accept(ast::visitors::CAbstractVisitor *visitor);

		void addNode(std::shared_ptr<ast::CNode> node);

		size_t getNodesSize() const;

		std::shared_ptr<ast::CNode> getNodeAt(size_t i) const;


	};

}