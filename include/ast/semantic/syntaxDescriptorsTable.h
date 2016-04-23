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
		 * \brief Abstract base class for other nodes.
		 */
		class CSyntaxDescriptorTable {
		  private:
			std::map<std::string, ptr(ast_descriptorinterface)> m_descriptorMap;

		  public:

			bool symbolFound(const std::string& name) const;

			void addSymbol(ptr(ast_descriptorinterface) node);

			ptr(ast_descriptorinterface) getSymbol(const std::string& name);

			void clear();
		};

	}
}
/*! @}*/