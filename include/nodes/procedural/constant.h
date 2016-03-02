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
                        /**< Integer 4B value */
			i32 m_intValue;

		  public:
			/**
			* Parametric constructor with default value
			* @param val: integer value
			*/
			CConstant(i32 val = 0);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& outStr) const;

			/**
			 * Integer value getter
			 * @return integer value
			 */
			i32 getValue() const;
		};

	}

}