#pragma once

#include <memory>
#include "abstractStatement.h"

namespace ast {

	/**
	 *  \addtogroup procedural
	 *  @{
	 */

	/**
	 * procedural Namespace to uniquely identify compo AST nodes.
	 */
	namespace procedural {

		/**
		 * \class CAbstractExpression
		 * \brief Class for abstract expression representation.
		 */
		class CAbstractExpression : public virtual CAbstractStatement {
		  public:
			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& outStr) const = 0;
		};

	}

}