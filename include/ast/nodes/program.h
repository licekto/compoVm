#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "ast/nodes/node.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {
		/**
		 * \class CProgram
		 * \brief AST to node that represents all top-level nodes in source file (i.e. descriptors and interfaces).
		 *
		 * CProgram node contains references to top-level nodes of Compo source file.
		         * CProgram inherits from std::enable_shared_from_this to enable shared_from_this shared pointer creation.
		 */
		class CProgram : public CNode, public std::enable_shared_from_this<CProgram> {
		  protected:
			/**< Vector of root nodes */
			std::vector<std::shared_ptr<CNode>> m_rootNodes;

		  public:
			/**
			* Default constructor
			*/
			CProgram();

			/**
			* Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

			/**
			 * Adds node pointer to the node vector
			 * @param node - processed node
			 */
			void addNode(std::shared_ptr<CNode> node);

			/**
			 * Number of nodes getter
			 * @return number of nodes in nodes vector
			 */
			size_t getNodesSize() const;

			/**
			 * Nodes getter
			 * @param i - index of wanted node
			 * @return shared pointer to node
			 */
			std::shared_ptr<CNode> getNodeAt(size_t i) const;
		};

	}

}