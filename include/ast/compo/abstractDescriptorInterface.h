#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/procedural/symbol.h"
#include "ast/procedural/compoundBody.h"
#include "ast/compo/serviceSignature.h"

namespace ast {

	namespace compo {

		/**
		 * \class CAbstractDescriptorInterface
		 * \brief Abstract base class for service and constraint nodes.
		 *
		 * Abstract base class for service and constraint nodes. Class inherits virtually from CCompoNode prevent diamond problem.
		 * This class was designed because of the similar structure of service a constraint nodes thus to prevent code repetition.
		 */
		class CAbstractDescriptorInterface : public virtual CNode {
		  protected:
                      /**< Descriptor name */
			std::shared_ptr<ast::procedural::CSymbol> m_name;

			/**< Inheritance information */
			std::shared_ptr<ast::procedural::CSymbol> m_extends;
                        
                public:
                        /**
			* Parametric constructor with default value
			* @param name: Name
			* @param atomic: Name of base
			*/
			CAbstractDescriptorInterface(std::shared_ptr<ast::procedural::CSymbol> name = nullptr,
                                                     std::shared_ptr<ast::procedural::CSymbol> extends = nullptr);
                    
                        /**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(ast::visitors::CAbstractVisitor *visitor) = 0;

			/**
			* Name getter
			* @return name symbol
			*/
			std::shared_ptr<ast::procedural::CSymbol> getNameSymbol() const;

			/**
			* Extends getter
			* @return name of parent class symbol
			*/
			std::shared_ptr<ast::procedural::CSymbol> getExtendsSymbol() const;
		};

	}

}