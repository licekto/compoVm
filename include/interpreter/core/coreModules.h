#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "definitions/allDefinitions.h"
#include "interpreter/config.h"
#include "interpreter/kernelModules.h"
#include "parser/parserWrapper.h"

namespace interpreter {

	namespace core {
		/**
		 * \class CKernelLoader
		 * \brief Kernel code loader class.
		 */
		class CCoreModules {
		  private:
                      std::map<coreModuleType, std::string> m_kernelComponentsCode;
                      
                      std::map<coreModuleType, ptr(ast_descriptor)> m_kernelComponentsAst;                      
                      
                      ptr(ParserWrapper) m_parser;
                      
                      std::string readFile(std::string path) const;
                      
		  public:
                      
                      CCoreModules(ptr(ParserWrapper) parser = nullptr);
                      
                      void loadModules();
                      
                      std::string getKernelModuleCode(coreModuleType module) const;
                      
                      ptr(ast_descriptor) getKernelModuleAst(coreModuleType module) const;
		};

	}
	/*! @}*/
}
/*! @}*/