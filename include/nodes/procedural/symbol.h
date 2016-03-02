#pragma once

#include <memory>
#include "nodes/node.h"
#include "abstractPrimaryExpression.h"


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
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			* StringValue getter
			* @return name string object
			*/
			std::string getStringValue() const;
		};

	}

}