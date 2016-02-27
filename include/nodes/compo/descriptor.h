#pragma once

#include "nodes/node.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CDescriptor
		 * \brief Class for Compo descriptor representation.
		 */
		class CDescriptor : public CNode {
		  private:
			nodes::procedural::CSymbol                  * m_name;         /**< Descriptor name */
			nodes::procedural::CSymbol                  * m_extends;      /**< Inheritance information */
			std::vector<nodes::CNode*>        m_body;         /**< Vector of descriptor body nodes */

		  public:
			/**
			* Parametric constructor with default values
			* @param name: Name of descriptor
			* @param extends: Name of parent descriptor
			* @param body: Vector of body nodes
			*/
			CDescriptor    (   nodes::procedural::CSymbol *name = nullptr,
			                   nodes::procedural::CSymbol *extends = nullptr,
			                   const std::vector<nodes::CNode*>& body = std::vector<nodes::CNode*>(0));

			/**
			* Copy constructor
			* Copy constructor is made protected to prevent from copying of object of this (abstract) type.
			* @param other: reference to another object of same type
			*/
			CDescriptor    (const CDescriptor& other);

			/**
			* Move constructor
			* Move constructor is made protected to prevent from moving of object of this (abstract) type.
			* @param other: rvalue-reference to another object of same type
			*/
			CDescriptor    (CDescriptor&& other) noexcept;

			/**
			* Copy assignment operator
			* Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CDescriptor&               operator =          (const CDescriptor& other);

			/**
			* Move assignment operator
			* Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CDescriptor&               operator =                  (CDescriptor&& other) noexcept;

			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual nodes::CNode *                    clone                       () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CDescriptor   ();

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print               (std::ostream& os) const;

			/**
			* Name getter
			* @return Name symbol
			*/
			std::string                     getName             () const;

			/**
			* Extends setter
			* @param Name of parent class symbol
			*/
			void                            setExtends          (nodes::procedural::CSymbol * extends);

			/**
			* Extends getter
			* @return Name of parent class symbol
			*/
			std::string                     getExtends          () const;

			/**
			 * Body vector size getter
			 * @return number of elements in body
			 */
			size_t                          getBodySize         () const;

			/**
			* Body getter
			* @return Constant pointer to body vector
			*/
			nodes::CNode *                    getBodyNodeAt       (int index) const;
		};

	}

}