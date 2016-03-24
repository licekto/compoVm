#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "definitions/allDefinitions.h"
#include "interpreter/config.h"
#include "interpreter/core/coreModuleType.h"
#include "parser/parserWrapper.h"
#include "exceptions/runtime/coreModuleNotFoundException.h"

namespace interpreter {

	namespace core {
		/**
		 * \class CKernelLoader
		 * \brief Kernel code loader class.
		 */
		class CCoreModules {
		  private:
			std::map<coreModuleType, ptr(ast_descriptor)> m_kernelComponents;

			ptr(ParserWrapper) m_parser;

			std::string readFile(std::string path) const;

                        void getModule(coreModuleType module, std::string path);
                        
		  public:

			CCoreModules(ptr(ParserWrapper) parser = nullptr);

			void loadModules();

			ptr(ast_descriptor) getKernelModule(coreModuleType module) const;
                        
                        void bootstrap();
		};

	}
	/*! @}*/
}
/*! @}*/