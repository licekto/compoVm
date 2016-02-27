#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/procedural/abstractExpression.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CAbstractPrimaryExpression
		 * \brief Class for primary expression like string literal, constant, identifier or expression in parentheses.
		 */
		class CAbstractPrimaryExpression : public virtual CAbstractExpression {
		  public:
			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print                   (std::ostream& outStr) const = 0;
		};

	}

}