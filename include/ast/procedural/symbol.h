#pragma once

#include <memory>
#include "abstractPrimaryExpression.h"
#include "ast/visitor/abstractStringVisitor.h"

namespace ast {

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
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);

			/**
			* StringValue getter
			* @return name string object
			*/
			std::string getStringValue() const;
		};

	}

}