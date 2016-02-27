#pragma once

#include <memory>
#include "nodes/node.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CAbstractStatement
		 * \brief Class for abstract statement representation.
		 */
		class CAbstractStatement : public virtual CNode {
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