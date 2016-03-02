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
		class CBreakStatement : public CAbstractStatement {
		  public:
                        /**
			* Default constructor
			*/
			CBreakStatement();
                      
			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;
		};

	}

}