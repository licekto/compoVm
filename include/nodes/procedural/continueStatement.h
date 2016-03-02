#pragma once

#include <memory>

#include "nodes/procedural/abstractStatement.h"
#include "nodes/procedural/abstractExpression.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CFor
		 * \brief Class for for-loop representation
		 */
		class CContinueStatement : public CAbstractStatement {
		  public:
			/**
			* Default constructor
					*/
			CContinueStatement();

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;
		};

	}

}