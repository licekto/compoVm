#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				class CPrimitiveService : public CAbstractPrimitive {

					std::function<ptr(objects::CGeneralPort)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> m_callback;

					std::vector<std::string> m_argumentsNames;

					std::vector<ptr(objects::CComponent)> m_arguments;

				  public:

					CPrimitiveService(const std::string& name = "",
					                  ptr(CComponent) context = nullptr,
					                  std::function<ptr(objects::CGeneralPort)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> callback
					                  = std::function<ptr(objects::CGeneralPort)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)>(),
					                  std::vector<std::string> argumentsNames = std::vector<std::string>(0));

					CPrimitiveService(ptr(CPrimitiveService) instance);

					virtual ~CPrimitiveService();

					ptr(CComponent) getOwner() = delete;

					void setOwner(ptr(CComponent) owner) = delete;

					void setContext(ptr(CComponent) context);

					ptr(CComponent) getContext();

					ptr(objects::CGeneralPort) invoke();

					size_t getArgumentsNamesCount() const;

					void setArgumentName(std::string argumentName);

					std::string getArgumentNameAt(size_t index);

					std::string getName() const;

					void addArgument(ptr(objects::CComponent) arg);

					size_t getArgumentCount() const;

					ptr(objects::CComponent) getArgumentAt(size_t index);

					void setCallback(std::function<ptr(objects::CGeneralPort)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> callback);
				};

			}
		}
	}
}