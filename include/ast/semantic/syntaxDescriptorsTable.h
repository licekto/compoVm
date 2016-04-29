#pragma once

#include <memory>
#include <map>
#include <string>

#include "exceptions/semantic/redefinedDescriptorException.h"
#include "exceptions/semantic/undefinedDescriptorException.h"
#include "exceptions/semantic/undefinedSymbolException.h"

#include "definitions/allDefinitions.h"

namespace ast {
	/**
	 *  \addtogroup core
	 *  @{
	 */

	/**
	 * core Namespace to uniquely identify compo AST nodes.
	 */
	namespace semantic {

		/**
		* \class CGLobalDescriptorTable
		 * \brief Descriptor table class
		 */
		class CSyntaxDescriptorTable {
		  private:
			/**< Hash map string -> reference */
			std::map<std::string, ptr(ast_descriptorinterface)> m_descriptorMap;

		  public:
			/**
			 * Looks for symbol name
			 * @param name - string
			 * @return bool
			 */
			bool symbolFound(const std::string& name) const;

			/**
			 * Adds symbol to table
			 * @param node - string
			 */
			void addSymbol(ptr(ast_descriptorinterface) node);

			/**
			 * Returns symbol with given name
			 * @param name - string
			 * @return reference
			 */
			ptr(ast_descriptorinterface) getSymbol(const std::string& name);

			/**
			 * Clears table
			 */
			void clear();
		};

	}
}
/*! @}*/