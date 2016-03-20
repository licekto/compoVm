#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/procedural/compoundBody.h"
#include "ast/nodes/compo/serviceSignature.h"

namespace ast {

    namespace nodes {
    
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
			std::shared_ptr<procedural::CSymbol> m_name;

			/**< Inheritance information */
			std::shared_ptr<procedural::CSymbol> m_extends;
                        
                public:
                        /**
			* Parametric constructor with default value
			* @param name: Name
			* @param atomic: Name of base
			*/
			CAbstractDescriptorInterface(std::shared_ptr<procedural::CSymbol> name = nullptr,
                                                     std::shared_ptr<procedural::CSymbol> extends = nullptr);
                    
                        /**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(visitors::CAbstractVisitor *visitor) = 0;

			/**
			* Name getter
			* @return name symbol
			*/
			std::shared_ptr<procedural::CSymbol> getNameSymbol() const;

			/**
			* Extends getter
			* @return name of parent class symbol
			*/
			std::shared_ptr<procedural::CSymbol> getExtendsSymbol() const;
		};

	}
        
    }

}