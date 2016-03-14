#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/compo/port.h"
#include "ast/procedural/symbol.h"
#include "ast/compo/signaturesPort.h"
#include "ast/compo/serviceSignature.h"

namespace ast {

	namespace compo {

		/**
		 * \class CDescriptor
		 * \brief Class for Compo descriptor representation.
		 */
		class CDescriptor : public CNode {
		  private:
			/**< Descriptor name */
			std::shared_ptr<ast::procedural::CSymbol> m_name;

			/**< Inheritance information */
			std::shared_ptr<ast::procedural::CSymbol> m_extends;

			/**< Vector of descriptor body nodes */
			std::vector<std::shared_ptr<ast::CNode>> m_body;

			/**< Every descriptor contains default port */
			std::shared_ptr<ast::compo::CPort> m_defaultPort;

		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of descriptor
			* @param extends: name of parent descriptor
			* @param body: vector of body nodes
			*/
			CDescriptor(std::shared_ptr<ast::procedural::CSymbol> name = nullptr,
			            std::shared_ptr<ast::procedural::CSymbol> extends = nullptr,
			            const std::vector<std::shared_ptr<ast::CNode>>& body = std::vector<std::shared_ptr<ast::CNode>>(0));

                        /**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);
                        
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
			std::shared_ptr<ast::CNode> getBodyNodeAt (int index) const;

			/**
			* Default port getter
					* @return Constant pointer to port
					*/
			std::shared_ptr<ast::compo::CPort> getDefaultPort() const;
		};

	}

}