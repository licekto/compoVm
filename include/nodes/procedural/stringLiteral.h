#pragma once

#include <memory>
#include "nodes/node.h"
#include "abstractPrimaryExpression.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CStringLiteral
		 * \brief Class for integer literal representation.
		 *
		 * Class contains positive or negative 4B integer value.
		 */
		class CStringLiteral : public CAbstractPrimaryExpression {
		  private:
                        /**< String value */
			std::string m_stringValue;

		  public:
			/**
			* Parametric constructor with default value
			* @param val: string value
			*/
			CStringLiteral(const std::string& val = "");

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& outStr) const;

			/**
			 * String value getter
			 * @return string value
			 */
			std::string getValue() const;
		};

	}

}