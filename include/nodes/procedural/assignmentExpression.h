#pragma once

#include "nodes/node.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CAssignment
		 * \brief Class for assignment representation.
		 */
		class CAssignmentExpression : public CNode {
		  private:
			CSymbol                  * m_variable;     /**< Variable to assign to */
			CNode                    * m_rValue;       /**< Right-hand side of assignment expression */

		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CAssignmentExpression         (CSymbol * variable = nullptr, CNode * rVal = nullptr);

			/**
			* Copy constructor
			* @param other: reference to another object of same type
			*/
			CAssignmentExpression         (const CAssignmentExpression& other);

			/**
			* Move constructor
			* @param other: rvalue-reference to another object of same type
			*/
			CAssignmentExpression         (CAssignmentExpression&& other) noexcept;

			/**
			* Copy assignment operator
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CAssignmentExpression&                    operator =          (const CAssignmentExpression& other);

			/**
			* Move assignment operator
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CAssignmentExpression&                    operator =          (CAssignmentExpression&& other) noexcept;

			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual CNode *                    clone               () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CAssignmentExpression        ();

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print               (std::ostream& os) const;

			/**
			* Variable name getter
			* @return Variable name
			*/
			CSymbol *                          getVariable         () const;

			/**
			* Right-hand side expression getter
			* @return Expression node
			*/
			CNode *                            getRValue           () const;
		};

	}

}