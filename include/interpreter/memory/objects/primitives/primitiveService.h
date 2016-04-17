#pragma once

#include <string>

#include "logger/logger.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponet;
			class CGeneralPort;

			namespace primitives {

				class CPrimitiveService : public CAbstractPrimitive {

					std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)> m_callback;

				  public:

					CPrimitiveService(const std::string& name = "",
					                  ptr(CComponent) context = nullptr,
					                  std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)> callback
					                  = std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)>());

					CPrimitiveService(ptr(CPrimitiveService) instance);

					virtual ~CPrimitiveService();

					ptr(CComponent) getOwner() = delete;

					void setOwner(ptr(CComponent) owner) = delete;

					void setContext(ptr(CComponent) context);

					ptr(CComponent) getContext();

					ptr(objects::CGeneralPort) invoke();

					void setCallback(std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)> callback);
				};

			}
		}
	}
}