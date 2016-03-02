#pragma once

#include <memory>
#include "nodes/node.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CArchitecture
		 * \brief Class for Compo architecture representation.
		 */
		class CArchitecture : public CNode {
		  public:
			/**
			* Default constructor
			*/
			CArchitecture();

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;
		};

	}

}