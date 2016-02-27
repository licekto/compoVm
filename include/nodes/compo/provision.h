#pragma once

#include "nodes/compo/abstractReqProv.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CProvision
		 * \brief Class for Compo provision node representation.
		 */
		class CProvision : public CAbstractReqProv {
		  public:
			/**
			* Parametric constructor with default value
			* @param type: Type of visibility
			* @param ports: Vector of ports
			*/
			CProvision     ( types::visibilityType type = types::visibilityType::EXTERNAL,
			                 const std::vector<compo::CPort*>& ports = std::vector<compo::CPort*>(0));

			/**
			* Copy constructor
			* @param other: reference to another object of same type
			*/
			CProvision     (const CProvision& other);

			/**
			* Move constructor
			* @param other: rvalue-reference to another object of same type
			*/
			CProvision     (CProvision&& other) noexcept;

			/**
			* Copy assignment operator
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CProvision&                operator=           (const CProvision& other);

			/**
			* Move assignment operator
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CProvision&                operator=           (CProvision&& other) noexcept;

			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual CNode *                    clone                   () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CProvision    ();
		};

	}

}