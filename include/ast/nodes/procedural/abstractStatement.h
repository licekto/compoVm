#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		/**
		 * \class CAbstractStatement
		 * \brief Class for abstract statement representation.
		 */
		class CAbstractStatement : public virtual CNode {
		  public:

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) = 0;
		};

	}
        
    }

}