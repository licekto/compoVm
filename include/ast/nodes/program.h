#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "ast/nodes/node.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {
    
    namespace nodes {
	/**
	 * \class CNode
	 * \brief Abstract base class for other nodes.
	 *
	 * Abstract base class of AST. Every node in AST is derived from this one.
	 */
	class CProgram : public CNode, public std::enable_shared_from_this<CProgram> {
	  protected:

		/**< Vector of root nodes */
		std::vector<std::shared_ptr<CNode>> m_rootNodes;

	  public:

		CProgram();

		/**
		* Accept method for visitor acceptation.
			 * @param visitor: Pointer to abstract visitor.
			 */
		virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

		void addNode(std::shared_ptr<CNode> node);

		size_t getNodesSize() const;

		std::shared_ptr<CNode> getNodeAt(size_t i) const;


	};
        
    }

}