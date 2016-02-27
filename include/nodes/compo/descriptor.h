#pragma once

#include <memory>
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
			std::shared_ptr<nodes::procedural::CSymbol>  m_name;         /**< Descriptor name */
			std::shared_ptr<nodes::procedural::CSymbol>  m_extends;      /**< Inheritance information */
			std::vector<std::shared_ptr<nodes::CNode>>        m_body;         /**< Vector of descriptor body nodes */

		  public:
			/**
			* Parametric constructor with default values
			* @param name: Name of descriptor
			* @param extends: Name of parent descriptor
			* @param body: Vector of body nodes
			*/
			CDescriptor    (   std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
			                   std::shared_ptr<nodes::procedural::CSymbol> extends = nullptr,
			                   const std::vector<std::shared_ptr<nodes::CNode>>& body = std::vector<std::shared_ptr<nodes::CNode>>(0));

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
			std::shared_ptr<nodes::CNode>                    getBodyNodeAt       (int index) const;
		};

	}

}