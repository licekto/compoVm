#pragma once

#include <memory>
#include "types.h"
#include "ast/nodes/procedural/abstractPrimaryExpression.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CConstant
			 * \brief Class for integer literal representation.
			 *
			 * Class contains positive or negative 4B integer value.
			 */
			class CBoolean : public CAbstractPrimaryExpression, public std::enable_shared_from_this<CBoolean> {
			  private:
				/**< Integer 4B value */
				bool m_value;

			  public:
				/**
				* Parametric constructor with default value
				* @param val: integer value
				*/
				CBoolean(bool val = false);

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Integer value getter
				 * @return integer value
				 */
				bool getValue() const;
			};

		}

	}

}