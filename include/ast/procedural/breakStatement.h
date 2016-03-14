#pragma once

#include <memory>

#include "ast/procedural/abstractStatement.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CBreakStatement
		 * \brief Class for break statement representation
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