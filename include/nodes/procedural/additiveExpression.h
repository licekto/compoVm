#pragma once

#include "nodes/node.h"
#include "nodes/procedural/binaryExpression.h"
#include "nodes/procedural/symbol.h"
#include "nodes/types/operatorType.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CAdditiveExpression
		 * \brief Class for assignment representation.
		 */
		class CAdditiveExpression : public CBinaryExpression {
		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CAdditiveExpression         ( CAbstractExpression * op1 = nullptr,
			                              CAbstractExpression * op2 = nullptr);

			/**
			* Copy constructor
			* @param other: reference to another object of same type
			*/
			CAdditiveExpression         (const CAdditiveExpression& other);

			/**
			* Move constructor
			* @param other: rvalue-reference to another object of same type
			*/
			CAdditiveExpression         (CAdditiveExpression&& other) noexcept;

			/**
			* Copy assignment operator
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CAdditiveExpression&                    operator =          (const CAdditiveExpression& other);

			/**
			* Move assignment operator
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CAdditiveExpression&                    operator =          (CAdditiveExpression&& other) noexcept;

			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual CNode *                    clone               () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CAdditiveExpression        ();
		};

	}

}