#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "definitions/allDefinitions.h"
#include "interpreter/config.h"
#include "interpreter/core/coreModuleType.h"
#include "parser/parserWrapper.h"
#include "exceptions/runtime/coreModuleNotFoundException.h"
#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace core {
		/**
		 * \class CKernelLoader
		 * \brief Kernel code loader class.
		 */
		class CCoreModules {
		  private:
			std::vector<ptr(ast_descriptor)> m_coreDescriptors;

			ptr(ParserWrapper) m_parser;

			std::string readFile(const std::string& path) const;

			void loadDescriptor(const std::string& path);

		  public:

			CCoreModules(ptr(ParserWrapper) parser = nullptr);

			void loadCoreModules();

			ptr(ast_descriptor) getCoreDescriptor(const std::string& module) const;

			ptr(ast_descriptor) getCoreDescriptorAt(size_t i) const;

			size_t getCoreDescriptorsSize() const;
		};

	}
}