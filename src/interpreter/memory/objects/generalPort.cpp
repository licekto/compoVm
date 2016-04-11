#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/values/stringComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			CGeneralPort::CGeneralPort(ptr(CComponent) port, types::visibilityType v, types::roleType t)
				: m_port(port), m_primitivePort(nullptr), m_visibility(v), m_type(t), m_primitive(false) {

			}

			CGeneralPort::CGeneralPort(ptr(primitives::CPrimitivePort) port, types::visibilityType v, types::roleType t)
				: m_port(nullptr), m_primitivePort(port), m_visibility(v), m_type(t), m_primitive(true) {

			}

			types::visibilityType CGeneralPort::getVisibility() const {
				return m_visibility;
			}

			types::roleType CGeneralPort::getRole() const {
				return m_type;
			}

			bool CGeneralPort::isPrimitive() const {
				return m_primitive;
			}

			ptr(CComponent) CGeneralPort::getPort() {
				return m_port;
			}

			ptr(primitives::CPrimitivePort) CGeneralPort::getPrimitivePort() {
				return m_primitivePort;
			}

			std::string CGeneralPort::getName() const {
				if (m_primitive) {
					return m_primitivePort->getName();
				} else {
					return cast(memory::objects::values::CStringComponent)
					       (m_port->getPortByName("name")->getPrimitivePort()->getConnectedPortAt(0)->getOwner())->getValue();
				}
			}

			std::shared_ptr<CComponent> CGeneralPort::getOwner() {
				if (m_primitive) {
					return m_primitivePort->getOwner();
				} else {
					return m_port->getPortByName("owner")->getPrimitivePort()->getConnectedPortAt(0)->getOwner();
				}
			}

			void CGeneralPort::setOwner(ptr(CComponent) owner) {
				if (m_primitive) {
					m_primitivePort->setOwner(owner);
				} else {
					return m_port->getPortByName("owner")->getPrimitivePort()->getConnectedPortAt(0)->setOwner(owner);
				}
			}

			size_t CGeneralPort::getConnectedPortsNumber() const {
				if (m_primitive) {
					return m_primitivePort->getConnectedPortsNumber();
				} else {
					return m_port->getPortByName("connectedPorts")->getConnectedPortsNumber();
				}
			}

			std::shared_ptr<objects::CGeneralPort> CGeneralPort::getConnectedPortAt(size_t index) {
				if (m_primitive) {
					return m_primitivePort->getConnectedPortAt(index);
				} else {
					return m_port->getPortByName("connectedPorts")->getConnectedPortAt(index);
				}
			}

			void CGeneralPort::connectPort(std::shared_ptr<objects::CGeneralPort> port) {
				if (m_primitive) {
					return m_primitivePort->connectPort(port);
				} else {
					return m_port->getPortByName("connectedPorts")->connectPort(port);
				}
			}

			void CGeneralPort::disconnectPortAt(size_t index) {
				if (m_primitive) {
					return m_primitivePort->disconnectPortAt(index);
				} else {
					return m_port->getPortByName("connectedPorts")->disconnectPortAt(index);
				}
			}

		}
	}
}
