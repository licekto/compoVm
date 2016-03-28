#include "interpreter/core/bootstrap.h"

namespace interpreter {

	namespace core {

		CBootstrap::CBootstrap(std::shared_ptr<core::CCoreModules> coreModules)
			: m_coreModules(coreModules) {
		}

		void CBootstrap::iterateAddPorts(std::shared_ptr<ast_reqprov> reqprov, std::function<void(memory::objects::portVisibility, memory::objects::portType, ptr(ast_port))> callback) {
			for (size_t i = 0; i < reqprov->getNumberOfPorts(); ++i) {
				memory::objects::portVisibility v = reqprov->getVisibilityType() == ast::nodes::types::visibilityType::EXTERNAL
				                                    ? memory::objects::portVisibility::EXTERNAL : memory::objects::portVisibility::INTERNAL;

				memory::objects::portType t = reqprov->getNodeType() == ast::nodes::types::REQUIREMENT
				                              ? memory::objects::portType::REQUIREMENT : memory::objects::portType::PROVISION;

				callback(v, t, reqprov->getPortAt(i));
			}
		}

		void CBootstrap::addPrimitivePorts(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor) {
			// lambda function
			auto callback = [this, &component](memory::objects::portVisibility v, memory::objects::portType t, ptr(ast_port) port) {
				if (port->isCollection()) {
					component->addPort(new_ptr(memory::objects::TPortProperties)(v, t, nullptr, new_ptr(memory::objects::primitives::CPrimitiveCollectionPort)(port->getNameSymbol()->getStringValue(), component)));
				} else {
					component->addPort(new_ptr(memory::objects::TPortProperties)(v, t, nullptr, new_ptr(memory::objects::primitives::CPrimitivePort)(port->getNameSymbol()->getStringValue(), component)));
				}
			};

			iterateAddPorts(descriptor->getInRequirement(), callback);
			iterateAddPorts(descriptor->getExRequirement(), callback);
			iterateAddPorts(descriptor->getInProvision(), callback);
			iterateAddPorts(descriptor->getExProvision(), callback);
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapPortComponent(ptr(ast_port) astPort, ptr(memory::objects::CComponent) owner) {
			ptr(memory::objects::CComponent) port = new_ptr(memory::objects::CComponent)();
			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Port");

			addPrimitivePorts(port, descriptor);

			std::string name = astPort->getNameSymbol()->getStringValue();

			cast(memory::objects::primitives::CPrimitivePort)(port->getPrimitivePortByName("name"))->setConnectedComponent(new_ptr(memory::objects::CStringComponent)(name));
			cast(memory::objects::primitives::CPrimitivePort)(port->getPrimitivePortByName("owner"))->setConnectedComponent(owner);

			return port;
		}

		void CBootstrap::addPorts(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor) {
			// lambda function
			auto callback = [this, &component](memory::objects::portVisibility v, memory::objects::portType t, ptr(ast_port) port) {
				component->addPort(new_ptr(memory::objects::TPortProperties)(v, t, bootstrapPortComponent(port, component)));
			};

			iterateAddPorts(descriptor->getInRequirement(), callback);
			iterateAddPorts(descriptor->getExRequirement(), callback);
			iterateAddPorts(descriptor->getInProvision(), callback);
			iterateAddPorts(descriptor->getExProvision(), callback);
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapServiceComponent(ptr(ast_service) astService, ptr(memory::objects::CComponent) context) {
			ptr(memory::objects::CComponent) service = new_ptr(memory::objects::CComponent)();

			addPorts(service, m_coreModules->getCoreDescriptor("Service"));

			auto connectComponentFunc = [&service](const std::string& name, ptr(memory::objects::CComponent) component) {
				cast(memory::objects::primitives::CPrimitiveCollectionPort)
				(service->getPortByName(name)->getPrimitivePortByName("connectedPorts"))->connectComponent(component);
			};

			connectComponentFunc("context", context);
			connectComponentFunc("serviceSign", bootstrapServiceSignatureComponent(astService->getSignature()));
			connectComponentFunc("code", new_ptr(memory::objects::CStringComponent)(astService->getBodyCode()));

			service->addPrimitiveService(new_ptr(memory::objects::primitives::CPrimitiveService)("execute", std::vector<std::string>(0), service));

			return service;
		}

		std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapServiceSignatureComponent(ptr(ast_servicesignature) /*astSignature*/) {
			ptr(memory::objects::CComponent) serviceSignature = new_ptr(memory::objects::CComponent)();

			addPorts(serviceSignature, m_coreModules->getCoreDescriptor("ServiceSignature"));

			return nullptr;
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapDescriptorComponent() {
			ptr(memory::objects::CComponent) component = new_ptr(memory::objects::CComponent)();
			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Descriptor");

			addPorts(component, descriptor);

			return nullptr;

		}

		void CBootstrap::boostrap() {
			if (m_coreModules.use_count()) {
				for (size_t i = 0; i < m_coreModules->getCoreDescriptorsSize(); ++i) {
					m_coreModules->getCoreDescriptorAt(i);
				}
			}
		}
	}
}