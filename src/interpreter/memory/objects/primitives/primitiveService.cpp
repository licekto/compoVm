#include "interpreter/memory/objects/primitives/primitiveService.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				CPrimitiveService::CPrimitiveService(const std::string& name,
				                                     ptr(objects::CComponent) context,
				                                     std::function<ptr(objects::CComponent)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> callback,
				                                     std::vector<std::string> params)
					: CAbstractPrimitive(name, nullptr),
					  m_params(params),
					  m_context(context),
					  m_callback(callback) {
				}

				CPrimitiveService::~CPrimitiveService() {
				}

				ptr(objects::CComponent) CPrimitiveService::operator()(const std::vector<ptr(objects::CComponent)>& params) {
                                        if (params.size() != m_params.size()) {
                                            // throw
                                        }
					return m_callback(params, m_context);
				}

				size_t CPrimitiveService::getParamsCount() const {
					return m_params.size();
				}

				void CPrimitiveService::setParam(std::string param) {
					m_params.push_back(param);
                                }

                                std::string CPrimitiveService::getParamAt(size_t index) {
                                    return m_params.at(index);
                                }

				std::string CPrimitiveService::getName() const {
					return m_name;
				}

				ptr(objects::CComponent) CPrimitiveService::getContext() {
					return m_context;
				}

				void CPrimitiveService::setCallback(std::function<ptr(objects::CComponent)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> callback) {
					m_callback = callback;
				}

			}

		}
	}
}