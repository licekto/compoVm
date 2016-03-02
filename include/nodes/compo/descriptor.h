#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/procedural/symbol.h"
#include "port.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CDescriptor
		 * \brief Class for Compo descriptor representation.
		 */
		class CDescriptor : public CNode {
		  private:
                        /**< Descriptor name */
			std::shared_ptr<nodes::procedural::CSymbol> m_name;
                        
                        /**< Inheritance information */
			std::shared_ptr<nodes::procedural::CSymbol> m_extends;
                        
                        /**< Vector of descriptor body nodes */
			std::vector<std::shared_ptr<nodes::CNode>> m_body;
                        
                        /**< Every descriptor contains default port */
                        std::shared_ptr<nodes::compo::CPort> m_defaultPort;

		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of descriptor
			* @param extends: name of parent descriptor
			* @param body: vector of body nodes
			*/
			CDescriptor(std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
			            std::shared_ptr<nodes::procedural::CSymbol> extends = nullptr,
			            const std::vector<std::shared_ptr<nodes::CNode>>& body = std::vector<std::shared_ptr<nodes::CNode>>(0));

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			* Name getter
			* @return name symbol
			*/
			std::string getName() const;

			/**
			* Extends getter
			* @return name of parent class symbol
			*/
			std::string getExtends() const;

			/**
			 * Body vector size getter
			 * @return number of elements in body
			 */
			size_t getBodySize () const;

			/**
			* Body getter
			* @return Constant pointer to body vector
			*/
			std::shared_ptr<nodes::CNode> getBodyNodeAt (int index) const;
                        
                        /**
			* Default port getter
			* @return Constant pointer to port
			*/
                        std::shared_ptr<nodes::compo::CPort> getDefaultPort() const;
		};

	}

}