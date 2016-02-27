#pragma once

#include "nodes/compo/abstractReqProv.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CRequirement
		 * \brief Class for Compo requirement node representation.
		 */
		class CRequirement : public CAbstractReqProv {
		  public:
			/**
			* Parametric constructor with default value
			* @param type: Type of visibility
			* @param ports: Vector of ports
			*/
			CRequirement       ( types::visibilityType type = types::visibilityType::EXTERNAL,
			                     const std::vector<compo::CPort*>& ports = std::vector<compo::CPort*>(0) );
			/**
			* Copy constructor
			* @param other: reference to another object of same type
			*/
			CRequirement       (const CRequirement& other);

			/**
			* Move constructor
			* @param other: rvalue-reference to another object of same type
			*/
			CRequirement       (CRequirement&& other) noexcept;

			/**
			* Copy assignment operator
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CRequirement&              operator=               (const CRequirement& other);

			/**
			* Move assignment operator
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CRequirement&              operator=               (CRequirement&& other) noexcept;

			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual nodes::CNode *                    clone                   () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CRequirement      ();
		};

	}

}