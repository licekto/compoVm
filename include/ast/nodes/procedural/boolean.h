#pragma once

#include <memory>
#include "types.h"
#include "ast/nodes/procedural/abstractPrimaryExpression.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CBoolean
			 * \brief Class for boolean value representation.
			 */
			class CBoolean : public CAbstractPrimaryExpression, public std::enable_shared_from_this<CBoolean> {
			  private:
				/**< Bool value */
				bool m_value;

			  public:
				/**
				* Parametric constructor with default value
				* @param val: bool value
				*/
				CBoolean(bool val = false);

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Bool value getter
				 * @return bool value
				 */
				bool getValue() const;
			};

		}

	}

}