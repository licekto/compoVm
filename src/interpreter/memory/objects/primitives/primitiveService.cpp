#include "interpreter/memory/objects/primitives/primitiveService.h"


namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				CPrimitiveService::CPrimitiveService(const std::string& name,
				                                     ptr(objects::CComponent) context,
				                                     std::function<ptr(objects::CGeneralPort)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> callback,
				                                     std::vector<std::string> argumentsNames)
					: CAbstractPrimitive(name, context),
					  m_callback(callback),
					  m_argumentsNames(argumentsNames),
					  m_arguments(std::vector<ptr(objects::CComponent)>(0)) {
				}

				CPrimitiveService::CPrimitiveService(ptr(CPrimitiveService) instance)
					: CAbstractPrimitive(instance),
					  m_callback(instance->m_callback) {
					for (const std::string& param : instance->m_argumentsNames) {
						m_argumentsNames.push_back(param);
					}
				}

				CPrimitiveService::~CPrimitiveService() {
				}

				ptr(CComponent) CPrimitiveService::getContext() {
					return m_owner;
				}

				void CPrimitiveService::setContext(std::shared_ptr<CComponent> context) {
					m_owner = context;
				}

				ptr(objects::CGeneralPort) CPrimitiveService::invoke() {
					return m_callback(m_arguments, m_owner);
				}

				size_t CPrimitiveService::getArgumentsNamesCount() const {
					return m_argumentsNames.size();
				}

				void CPrimitiveService::setArgumentName(std::string argumentName) {
					m_argumentsNames.push_back(argumentName);
				}

				std::string CPrimitiveService::getArgumentNameAt(size_t index) {
					std::string argument;
					try {
						argument = m_argumentsNames.at(index);
					} catch (const std::out_of_range& ex) {
						TRACE(ERROR, "Arguments names index out of range exception: " << ex.what());
					}
					return argument;
				}

				std::string CPrimitiveService::getName() const {
					return m_name;
				}

				void CPrimitiveService::addArgument(std::shared_ptr<objects::CComponent> arg) {
					m_arguments.push_back(arg);
				}

				size_t CPrimitiveService::getArgumentCount() const {
					return m_arguments.size();
				}

				std::shared_ptr<objects::CComponent> CPrimitiveService::getArgumentAt(size_t index) {
					ptr(objects::CComponent) component;
					try {
						component = m_arguments.at(index);
					} catch (const std::out_of_range& ex) {
						TRACE(ERROR, "Connected ports index out of range exception: " << ex.what());
					}
					return component;
				}

				void CPrimitiveService::setCallback(std::function<ptr(objects::CGeneralPort)(const std::vector<ptr(objects::CComponent)>&, const ptr(objects::CComponent)&)> callback) {
					m_callback = callback;
				}

			}

		}
	}
}