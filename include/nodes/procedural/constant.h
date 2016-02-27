#pragma once

#include <memory>
#include "nodes/node.h"
#include "types.h"
#include "abstractPrimaryExpression.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CConstant
		 * \brief Class for integer literal representation.
		 *
		 * Class contains positive or negative 4B integer value.
		 */
		class CConstant : public CAbstractPrimaryExpression {
		  private:
			i32                             m_intValue;         /**< Integer 4B value */

		  public:
			/**
			* Parametric constructor with default values
			* @param type: type of node
			* @param val: integer value
			*/
			CConstant           (i32 val = 0);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print               (std::ostream& outStr) const;

			/**
			 * Integer value getter
			 * @return integer value
			 */
			i32                             getValue            () const;
		};

	}

}