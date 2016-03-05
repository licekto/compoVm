#pragma once

#include <memory>

#include "nodes/procedural/abstractStatement.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CContinueStatement
		 * \brief Class for continue statement representation
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