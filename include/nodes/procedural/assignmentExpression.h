#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CAssignment
		 * \brief Class for assignment representation.
		 */
		class CAssignmentExpression : public CNode {
		  private:
			std::shared_ptr<nodes::procedural::CSymbol> m_variable;     /**< Variable to assign to */
			std::shared_ptr<nodes::CNode> m_rValue;       /**< Right-hand side of assignment expression */

		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CAssignmentExpression         (std::shared_ptr<nodes::procedural::CSymbol> variable = nullptr, std::shared_ptr<nodes::CNode> rVal = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print               (std::ostream& os) const;

			/**
			* Variable name getter
			* @return Variable name
			*/
			std::shared_ptr<nodes::procedural::CSymbol>                          getVariable         () const;

			/**
			* Right-hand side expression getter
			* @return Expression node
			*/
			std::shared_ptr<nodes::CNode>                            getRValue           () const;
		};

	}

}