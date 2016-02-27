#pragma once

#include "nodes/compo/abstractServConstr.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CConstraint
		 * \brief Class for Compo constraint representation.
		 */
		class CConstraint : public CAbstractServConstr {
		  public:
			/**
			* Parametric constructor with default values
			* @param name: Name of constraint
			* @param params: Vector of parameters
			* @param body: Vector of body expressions
			*/
			CConstraint    ( nodes::procedural::CSymbol *name = nullptr,
			                 const std::vector<nodes::procedural::CSymbol*>& params = std::vector<nodes::procedural::CSymbol*>(0),
			                 const std::vector<nodes::CNode*>& body = std::vector<nodes::CNode*>(0));
			/**
			* Copy constructor
			* Copy constructor is made protected to prevent from copying of object of this (abstract) type.
			* @param other: reference to another object of same type
			*/
			CConstraint    (const CConstraint& other);

			/**
			* Move constructor
			* Move constructor is made protected to prevent from moving of object of this (abstract) type.
			* @param other: rvalue-reference to another object of same type
			*/
			CConstraint    (CConstraint&& other) noexcept;

			/**
			* Copy assignment operator
			* Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CConstraint&               operator =          (const CConstraint& other);

			/**
			* Move assignment operator
			* Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CConstraint&               operator =          (CConstraint&& other) noexcept;

			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual nodes::CNode *                    clone               () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CConstraint   ();
		};

	}

}