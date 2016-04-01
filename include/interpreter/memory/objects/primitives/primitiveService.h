#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				class CPrimitiveService : public CAbstractPrimitive {

					std::vector<std::string> m_params;

					ptr(objects::CComponent) m_context;

					std::function<ptr(objects::CComponent)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> m_callback;

				  public:

					CPrimitiveService(const std::string& name = "",
                                                          ptr(CComponent) context = nullptr,
					                  std::function<ptr(objects::CComponent)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> callback
                                                            = std::function<ptr(objects::CComponent)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)>(),
                                                          std::vector<std::string> params = std::vector<std::string>(0));

					virtual ~CPrimitiveService();

					ptr(objects::CComponent) operator()(const std::vector<ptr(objects::CComponent)>& params);

					size_t getParamsCount() const;

					void setParam(std::string param);
                                        
                                        std::string getParamAt(size_t index);

					std::string getName() const;

					ptr(objects::CComponent) getContext();

					void setCallback(std::function<ptr(objects::CComponent)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> callback);
				};

			}
		}
	}
}