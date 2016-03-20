#pragma once

#include <memory>
#include "ast/nodes/procedural/abstractPrimaryExpression.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {
    
    namespace nodes {

	namespace procedural {

		/**
		 * \class CSymbol
		 * \brief Class for Compo symbol node representation.
		 */
		class CSymbol : public CAbstractPrimaryExpression {
		  private:
			/**< Name of symbol */
			std::string m_name;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: string name
			*/
			CSymbol(const std::string& name);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(visitors::CAbstractVisitor *visitor);

			/**
			* StringValue getter
			* @return name string object
			*/
			std::string getStringValue() const;
		};

	}
        
    }

}